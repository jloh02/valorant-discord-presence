#include "riot_api_connection.h"

std::string lockfile[5];

namespace valorant {
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

	std::string remote_connect(std::string endpoint) {
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
		std::cout << res.error() << std::endl;
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
			std::cout << valorant::credentials["puuid"] << std::endl;

			/*---------------------------------Access localhost for presences---------------------------------*/
			if (!getPresence()) continue;
			break;
		}
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
}