#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

#include "discord_handler.h"

#include "httplib/httplib.h"
#include "base64/base64.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

namespace valorant {
	struct GameData {
		std::string agentID, mapID;
		uint64_t timeLeft;
	};

	inline std::map<std::string, std::string> credentials;
	void initialize();
	bool getPresence();

	void getMatchID(bool pregame);
	GameData getGameDetails(bool pregame);
}