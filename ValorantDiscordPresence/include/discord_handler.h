#pragma once

#include <iostream>
#include <memory>
#include <format>

#include "discord-sdk/discord.h"
#include "riot_api_connection.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

struct DiscordState
{
	discord::User currentUser;
	std::unique_ptr <discord::Activity> activity;
	std::unique_ptr<discord::Core> core;
};

inline DiscordState state;

namespace disc {
	void initialize();
	void updateActivity(rapidjson::GenericArray<false, rapidjson::Value> presences);
	void updateActivity(const char* actState, const char* actDetails, time_t startT, time_t endT, const char* smallImg, const char* largeImg);
}
