#include "riot_api_connection.h"

ix::WebSocket ws;
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
			std::string presences;
			if ((presences = localhost_connect("/chat/v4/presences")).empty()) continue;
			rapidjson::Document presenceDoc;
			presenceDoc.Parse(presences.c_str());
			if (presenceDoc.HasParseError()) {
				std::this_thread::sleep_for(std::chrono::seconds(5));
				continue;
			}
			auto presenceTmp = presenceDoc.FindMember("presences");
			if (presenceTmp == presenceDoc.MemberEnd()) {
				std::this_thread::sleep_for(std::chrono::seconds(5));
				continue;
			}
			disc::updateActivity((presenceTmp->value).GetArray());

			/*---------------------------------Setup Websocket to Listen---------------------------------*/
			ix::initNetSystem();
			char wslink[128];
			sprintf_s(wslink, "wss://riot:%s@localhost:%s", lockfile[3].c_str(), lockfile[2].c_str());
			ws.setUrl(std::string(wslink));

			ix::SocketTLSOptions opt;
			opt.caFile = "NONE";
			ws.setTLSOptions(opt);

			ix::WebSocketHttpHeaders wssHeaders;
			wssHeaders.insert({ "Authorization", valorant::credentials["basicPassword"] });
			ws.setExtraHeaders(wssHeaders);

			std::cout << "Connecting to " << ws.getUrl() << "..." << std::endl;

			ws.setOnMessageCallback([=](const ix::WebSocketMessagePtr& msg)
				{
					if (msg->type == ix::WebSocketMessageType::Message)
					{
						if (!msg->str.empty() && msg->str.find(valorant::credentials["puuid"]) != std::string::npos) {
							rapidjson::Document wssDoc;
							wssDoc.Parse((msg->str).c_str());
							if (wssDoc.HasParseError()) return;
							disc::updateActivity(((wssDoc[2].GetObj())["data"].GetObj())["presences"].GetArray());
						}
					}
					else if (msg->type == ix::WebSocketMessageType::Open)
					{
						std::cout << "Connection established" << std::endl;
						std::cout << "> " << std::flush;
					}
					else if (msg->type == ix::WebSocketMessageType::Error)
					{
						// Maybe SSL is not configured properly
						//std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
						std::cout << "> " << std::flush;
					}

					ws.send("[5, \"OnJsonApiEvent_chat_v4_presences\"]");
					if (ws.getReadyState() != ix::ReadyState::Open) exit(0);
				}
			);
			ws.start();
			std::this_thread::sleep_for(std::chrono::seconds(5));
			if (ws.getReadyState() == ix::ReadyState::Closed) {
				ws.stop();
				continue;
			}
			break;
		}
	}
}