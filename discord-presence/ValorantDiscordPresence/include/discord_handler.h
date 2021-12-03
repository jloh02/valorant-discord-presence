#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <format>

#include "utils.h"
#include "riot_api_connection.h"

#include "discord-rpc/discord_rpc.h"
#include "discord-rpc/discord_register.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#define APPLICATION_ID "886156186653687838"

inline DiscordRichPresence activity;

namespace disc {
	void initialize(volatile bool* interrupt);
	void updateActivity(rapidjson::GenericArray<false, rapidjson::Value> presences);
	void updateActivity(const char* actState, const char* actDetails, time_t startT, time_t endT, const char* smallImg, const char* largeImg, bool inviteAvailable);
}
