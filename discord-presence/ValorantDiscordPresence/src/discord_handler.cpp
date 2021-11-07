#include "discord_handler.h"

#define DEBUG_UPDATE_ACTIVITY	//Print intermediary debug statements when updating activity
#define DEBUG_ACTIVITY		//Print debug statements whenever using Discord SDK to update activity

namespace disc {
	namespace {
		time_t timeStart;	//Used to track start of game

		//Global variables to prevent deleted pointers
		discord::Core* core{};
		discord::Activity act{};

		std::string prevState; //"menu", "queue", "select", "game"
	}

	void initialize() {
		discord::Result result = discord::Core::Create(886156186653687838, DiscordCreateFlags_NoRequireDiscord, &core);
		if (result != discord::Result::Ok) {
			std::cout << "Discord not opened/installed\n";
			exit(0); //Exit if unable to connect to Discord (Not installed or closed)
		}
		state.core.reset(core);
		state.activity.reset(&act);

		if (!state.core)
		{
			std::cout << "Failed to instantiate discord core! (err " << static_cast<int>(result)
				<< ")\n";
			std::exit(-1);
		}

		state.core->SetLogHook(
			discord::LogLevel::Debug, [](discord::LogLevel level, const char* message)
			{ std::cerr << "Log(" << static_cast<uint32_t>(level) << "): " << message << "\n"; });

		//Default load-in activity status
		state.activity->GetAssets().SetLargeText("");
		state.activity->GetAssets().SetSmallText("");
		state.activity->SetType(discord::ActivityType::Playing);
		disc::updateActivity("", "Loading In...", NULL, NULL, "", "valorant_icon");

		discord::Result cbRes = state.core->RunCallbacks();
		if (cbRes != discord::Result::Ok) {
			std::cout << "Unable to connect to Discord: " << static_cast<int>(cbRes) << std::endl;
			exit(0);
		}
	}

	void updateActivity(rapidjson::GenericArray<false, rapidjson::Value> presences) {
		for (auto& a : presences) {
			if (!strcmp(a["puuid"].GetString(), valorant::credentials["puuid"].c_str())) {
#ifdef DEBUG_UPDATE_ACTIVITY
				std::cout << base64_decode(a["private"].GetString()) << std::endl;
#endif
				rapidjson::Document presenceDoc;
				presenceDoc.Parse(base64_decode(a["private"].GetString()).c_str());
				if (presenceDoc.HasParseError() || !presenceDoc["isValid"].GetBool()) continue;

				std::string gameType = presenceDoc["queueId"].GetString();
				gameType[0] = toupper(gameType[0]);
				if (strlen(gameType.c_str()) == 0) gameType = "Custom";

				if (presenceDoc["isIdle"].GetBool()) //Idle state
					updateActivity("", "Idle", NULL, NULL, "", "valorant_icon");
				else {
					if (!strcmp(presenceDoc["sessionLoopState"].GetString(), "MENUS")) { //In lobby
						bool isQueue = !strcmp(presenceDoc["partyState"].GetString(),"MATCHMAKING");

						if (isQueue && strcmp(prevState.c_str(), "queue")) timeStart = std::time(0);
						prevState = isQueue ? "queue" : "menu";

						updateActivity(
							std::format("{} ({} of {})", isQueue ? "In Queue" : "In Lobby",
								presenceDoc["partySize"].GetInt(),
								presenceDoc["maxPartySize"].GetInt()).c_str(),
							gameType.c_str(),
							isQueue ? timeStart : NULL,
							NULL,
							"",
							"valorant_icon"
						);
					}
					else {
						//Agent select
						if (!strcmp(presenceDoc["sessionLoopState"].GetString(), "PREGAME")) {
							if (strcmp(prevState.c_str(), "select")) valorant::getMatchID(true);
							prevState = "select";

							valorant::GameData gd = valorant::getGameDetails(true);

							updateActivity("Agent Select", gameType.c_str(), NULL, std::time(0) + (gd.timeLeft / 1000000000), gd.agentID.empty() ? "valorant_icon" : gd.agentID.c_str(), gd.mapID.c_str());
						}
						//In game
						else if (!strcmp(presenceDoc["sessionLoopState"].GetString(), "INGAME")) {
							if (strcmp(prevState.c_str(), "game")) {
								valorant::getMatchID(false);
								timeStart = std::time(0);
							}
							prevState = "game";

							valorant::GameData gd = valorant::getGameDetails(false);

							if (gd.mapID == "range" || gd.mapID.empty()) //In range
								updateActivity("In Range", "", timeStart, NULL, "valorant_icon", "range");
							else {	//Online game
								updateActivity(
									std::format("{} ({} {})",
										gameType,
										presenceDoc["partySize"].GetInt(),
										strcmp(gameType.c_str(), "Custom") ? "stack" : std::format("of {}", presenceDoc["maxPartySize"].GetInt())
									).c_str(),
									std::format("{} - {}", std::to_string(presenceDoc["partyOwnerMatchScoreAllyTeam"].GetInt()), std::to_string(presenceDoc["partyOwnerMatchScoreEnemyTeam"].GetInt())).c_str(),
									timeStart,
									NULL,
									gd.agentID.empty() ? "valorant_icon" : gd.agentID.c_str(),
									gd.mapID.c_str()
								);
							}
						}
					}
				}
				break;
			}
		}
	}

	void printActivity() { //Pretty print activity details
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		writer.StartObject();
		writer.String("state");
		writer.String(state.activity->GetState());
		writer.String("details");
		writer.String(state.activity->GetDetails());
		writer.String("timestamp");
		writer.StartObject();
		writer.String("start");
		writer.Int64(state.activity->GetTimestamps().GetStart());
		writer.String("end");
		writer.Int64(state.activity->GetTimestamps().GetEnd());
		writer.EndObject();
		writer.String("assets");
		writer.StartObject();
		writer.String("small");
		writer.String(state.activity->GetAssets().GetSmallImage());
		writer.String("large");
		writer.String(state.activity->GetAssets().GetLargeImage());
		writer.EndObject();
		writer.EndObject();
		std::cout << buffer.GetString() << std::endl;
	}

	void updateActivity(const char* actState, const char* actDetails, time_t startT, time_t endT, const char* smallImg, const char* largeImg) {
		state.activity->SetState(actState);
		state.activity->SetDetails(actDetails);
		state.activity->GetTimestamps().SetStart(startT);
		state.activity->GetTimestamps().SetEnd(endT);
		state.activity->GetAssets().SetSmallImage(smallImg);
		state.activity->GetAssets().SetLargeImage(largeImg);
#ifdef DEBUG_ACTIVITY
		printActivity();
#endif
		//state.core->ActivityManager().ClearActivity([](discord::Result result) {});
		state.core->ActivityManager().UpdateActivity(*(state.activity), [](discord::Result result) {
#ifdef DEBUG_ACTIVITY
			std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
			if (result != discord::Result::Ok) std::cout << static_cast<int>(result) << std::endl;
#endif
		});
	}
}