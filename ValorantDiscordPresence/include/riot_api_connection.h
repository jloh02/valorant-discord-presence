#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "discord_handler.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib/httplib.h"
#include "base64/base64.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

namespace valorant {
	inline std::map<std::string, std::string> credentials;
	void initialize();
	bool getPresence();
}