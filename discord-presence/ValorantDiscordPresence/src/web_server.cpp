#include "web_server.h"

namespace server {
	httplib::Server svr;

	bool initialize() {
		svr.Get("/ping", [](const httplib::Request& req, httplib::Response& res) {
			res.set_header("Access-Control-Allow-Origin", "https://jloh02.github.io");
			res.set_content("pong", "text/plain");
			});
		svr.Post("/join", [](const httplib::Request& req, httplib::Response& res) {
			res.set_header("Access-Control-Allow-Origin", "https://jloh02.github.io");
			rapidjson::Document reqDoc;
			reqDoc.Parse(req.body.c_str());

			std::pair<int, std::string> r = valorant::invite::joinParty((reqDoc.FindMember("party")->value).GetString(), (reqDoc.FindMember("puuid")->value).GetString());
			if (r.first != 200) {
				if (r.second == "PARTY_NOT_FOUND")
					r.second = "Party not found.\nAre you in the same region as the party leader?";
				else if (r.second == "PLAYER_DOES_NOT_EXIST")
					r.second = "Player not found.\nAre you sure you are online?";
				else if (r.second == "INTERNAL_UNHANDLED_SERVER_ERROR")
					r.second = "Internal server error. Stop trying to join your own party!";
				else
					r.second = "An unknown error occured. Please contact the developer if this error persist.";
			}

			res.status = r.first;
			res.set_content(r.second, "text/plain");
			});
		return svr.bind_to_port("localhost", LOCAL_PORT);
	}

	void listenAsync() {
		svr.listen_after_bind();
	}

	void stop() {
		svr.stop();
	}
}