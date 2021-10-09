#include "riot_api_connection.h"

std::string lockfile[5];

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

	std::string getMatchID() {
		std::string res = remote_connect("/pregame/v1/players", valorant::credentials["puuid"]);
		rapidjson::Document pregameDoc;
		pregameDoc.Parse(res.c_str());
		return (pregameDoc.FindMember("MatchID")->value).GetString();
	}
}