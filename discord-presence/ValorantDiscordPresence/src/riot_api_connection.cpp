#include "riot_api_connection.h"

std::string lockfile[5] = {};
std::string matchID;

namespace valorant {
	bool getToken();

	std::string localhost_connect(std::string endpoint) {
		char link[128];
		sprintf_s(link, "https://127.0.0.1:%s", lockfile[2].c_str());
		httplib::Client cli(link);
		cli.enable_server_certificate_verification(false);
		httplib::Headers headers = {
			{ "Authorization", valorant::credentials["basicPassword"]}
		};
		auto res = cli.Get(endpoint.c_str(), headers);
		if (res.error() == httplib::Error::Success)
			return res->body;
		std::cerr << res.error() << std::endl;
		return "";
	}

	std::string remote_connect(std::string endpoint, std::string id) {
		getToken();
		httplib::Client cli(std::format("https://glz-{}-1.{}.a.pvp.net", valorant::credentials["region"], valorant::credentials["region"]));
		cli.enable_server_certificate_verification(false);
		httplib::Headers headers = {
			{ "X-Riot-Entitlements-JWT", valorant::credentials["entitlement"]},
			{ "Authorization", valorant::credentials["bearerToken"]}
		};
		//std::cout << std::format("https://glz-{}-1.{}.a.pvp.net{}/{}", valorant::credentials["region"], valorant::credentials["region"], endpoint, id) << std::endl << valorant::credentials["entitlement"] << std::endl << valorant::credentials["bearerToken"] << std::endl;
		auto res = cli.Get(std::format("{}/{}", endpoint, id).c_str(), headers);
		if (res.error() == httplib::Error::Success)
			return res->body;
		std::cerr << res.error() << std::endl;
		return "";
	}

	void initialize() {
		/*---------------------------------Retrieve Lockfile Credentials---------------------------------*/
		char lockfilePath[128];
		const char* lockfileSub = "\\Riot Games\\Riot Client\\Config\\lockfile";
		while (true) {
			//Read local appdata location
			char* buf = nullptr;
			size_t sz = 128;
			if (_dupenv_s(&buf, &sz, "LOCALAPPDATA") == 0 && buf != nullptr) {
				strcpy_s(lockfilePath, sizeof lockfilePath, buf);
				free(buf);

				strcat_s(lockfilePath, lockfileSub);

				//Read lockfile
				std::ifstream f(lockfilePath);
				std::string lockfileCont((std::istreambuf_iterator<char>(f)),
					std::istreambuf_iterator<char>());
				f.close();

				//Split lockfile contents into string array
				size_t startPos = 0, pos = 0, c = 0;
				while ((pos = lockfileCont.find(":", startPos)) != std::string::npos) {
					std::string found = lockfileCont.substr(startPos, pos - startPos);
					//std::cout << startPos << ' ' << pos << " " << " " << found << std::endl;
					lockfile[c++] = found;
					startPos = pos + 1;
				}
				lockfile[c] = lockfileCont.substr(startPos);
			}

			std::string password("riot:");
			password.append(lockfile[3]);
			std::string encodedPassword = base64_encode(password);
			valorant::credentials["b64Password"] = encodedPassword;
			std::string authHeader("Basic ");
			authHeader.append(encodedPassword);
			valorant::credentials["basicPassword"] = std::string(authHeader);

			/*---------------------------------Access localhost for PUUID---------------------------------*/
			std::string puuidRes = localhost_connect("/chat/v1/session");
			rapidjson::Document puuidDoc;
			puuidDoc.Parse(puuidRes.c_str());
			if (puuidDoc.HasParseError()) continue;
			auto puuidTmp = puuidDoc.FindMember("puuid");
			if (puuidTmp == puuidDoc.MemberEnd()) continue;
			valorant::credentials["puuid"] = (puuidTmp->value).GetString();
			//std::cout << valorant::credentials["puuid"] << std::endl;

			/*---------------------------------Access localhost for region---------------------------------*/
			std::string extSessionRes = localhost_connect("/product-session/v1/external-sessions");
			std::string regionSearch = "-ares-deployment=";
			size_t regIdx = extSessionRes.find(regionSearch);
			if (regIdx == std::string::npos) continue;
			valorant::credentials["region"] = extSessionRes.substr(regIdx + regionSearch.length(), 2);
			//std::cout << valorant::credentials["region"] << std::endl;

			/*---------------------------------Access localhost for entitlements---------------------------------*/
			if (!getToken()) continue;
			/*---------------------------------Access localhost for presences---------------------------------*/
			if (!getPresence()) continue;

			break;
		}
	}

	bool getToken() { //Riot resets tokens hourly
		std::string entRes = localhost_connect("/entitlements/v1/token");
		rapidjson::Document entDoc;
		entDoc.Parse(entRes.c_str());
		if (entDoc.HasParseError()) return false;
		auto tmp = entDoc.FindMember("accessToken");
		if (tmp == entDoc.MemberEnd()) return false;
		valorant::credentials["token"] = (tmp->value).GetString();
		tmp = entDoc.FindMember("token");
		if (tmp == entDoc.MemberEnd()) return false;
		valorant::credentials["entitlement"] = (tmp->value).GetString();
		//std::cout << valorant::credentials["token"] << std::endl << valorant::credentials["entitlement"] << std::endl;

		std::string bearerPW = "Bearer ";
		bearerPW.append(valorant::credentials["token"]);
		valorant::credentials["bearerToken"] = bearerPW;
		return true;
	}

	bool getPresence() {
		std::string presences;
		if ((presences = localhost_connect("/chat/v4/presences")).empty()) return false;
		rapidjson::Document presenceDoc;
		presenceDoc.Parse(presences.c_str());
		if (presenceDoc.HasParseError()) {
			std::this_thread::sleep_for(std::chrono::seconds(5));
			return false;
		}
		auto presenceTmp = presenceDoc.FindMember("presences");
		if (presenceTmp == presenceDoc.MemberEnd()) {
			std::this_thread::sleep_for(std::chrono::seconds(5));
			return false;
		}
		disc::updateActivity((presenceTmp->value).GetArray());
		return true;
	}

	void getMatchID(bool pregame) {
		std::string res = remote_connect(pregame ? "/pregame/v1/players" : "/core-game/v1/players", valorant::credentials["puuid"]);
		rapidjson::Document pregameDoc;
		pregameDoc.Parse(res.c_str());
		matchID = (pregameDoc.FindMember("MatchID")->value).GetString();
	}

	GameData getGameDetails(bool pregame) {
		std::string res = remote_connect(pregame ? "/pregame/v1/matches" : "/core-game/v1/matches", matchID);
		if (res.find("404") != std::string::npos) return { "" , "" , 0 };
		rapidjson::Document pregameDoc;
		pregameDoc.Parse(res.c_str());

		std::string agent;
		rapidjson::GenericArray<false, rapidjson::Value> allyPlayers = ((pregame ? (pregameDoc.FindMember("AllyTeam")->value) : pregameDoc).FindMember("Players")->value).GetArray();
		for (auto& p : allyPlayers) {
			std::string subj = ((p.FindMember("PlayerIdentity")->value).FindMember("Subject")->value).GetString();
			if (subj == credentials["puuid"]) agent = (p.FindMember("CharacterID")->value).GetString();
		}
		agent.erase(std::remove(agent.begin(), agent.end(), '-'), agent.end());

		std::string map = (pregameDoc.FindMember("MapID")->value).GetString();
		size_t lastSlash = map.rfind("/");
		if (lastSlash != std::string::npos) map = map.substr(lastSlash + 1);
		map[0] = tolower(map[0]);

		return { agent, map , pregame ? (pregameDoc.FindMember("PhaseTimeRemainingNS")->value).GetUint64() : 0 };
	}

	namespace invite {
		std::pair<int, std::string> remote_post_connect(std::string endpoint, std::string ownerPuuid) {
			httplib::Client cli(std::format("https://glz-{}-1.{}.a.pvp.net", credentials["region"], credentials["region"]));
			cli.enable_server_certificate_verification(false);
			httplib::Headers headers = {
				{ "Content-Type", "application/json"},
				{ "X-Riot-Entitlements-JWT", credentials["entitlement"]},
				{ "Authorization", credentials["bearerToken"]}
			};

			std::string bod = "{\"Subjects\":[\"";
			bod.append(ownerPuuid);
			bod.append("\"]}");

			auto res = cli.Post(endpoint.c_str(), headers, bod, "application/json");
			
			rapidjson::Document resDoc;
			resDoc.Parse(res->body.c_str());
			return { res->status , res->status==200?"Success":(resDoc.FindMember("errorCode")->value).GetString()};
		}

		std::pair<int, std::string> joinParty(std::string partyId, std::string ownerPuuid) {
			getToken();
			std::pair<int, std::string> res = remote_post_connect(std::format("/parties/v1/parties/{}/request", partyId), ownerPuuid);

			if (res.first == 400 && res.second == "REQUEST_OPEN_PARTY")
				res = remote_post_connect(std::format("/parties/v1/players/{}/joinparty/{}", credentials["puuid"], partyId), ownerPuuid);

			return res;
		}
	}
}