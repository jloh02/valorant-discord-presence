#include "discord_handler.h"

#define EMPTY_IMAGE ""//std::string(128,'\0').c_str()

namespace disc {

	namespace {
		time_t timeStart;
		discord::Core* core{};
		discord::Activity act{};

		std::string prevState; //"menu", "queue", "select", "game"
	}

	void initialize() {
		discord::Result result = discord::Core::Create(886156186653687838, DiscordCreateFlags_Default, &core);
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

		state.core->ActivityManager().RegisterCommand("\"C:/Riot Games/Riot Client/RiotClientServices.exe\" --launch-product=valorant --launch-patchline=live");

		state.activity->GetAssets().SetLargeText("");
		state.activity->GetAssets().SetSmallText("");
		state.activity->SetType(discord::ActivityType::Playing);
		disc::updateActivity("", "Loading In...", NULL, NULL, EMPTY_IMAGE, "valorant_icon");
	}

	void updateActivity(rapidjson::GenericArray<false, rapidjson::Value> presences) {
		for (auto& a : presences) {
			if (!strcmp(a["puuid"].GetString(), valorant::credentials["puuid"].c_str())) {
				std::cout << base64_decode(a["private"].GetString()) << std::endl;

				rapidjson::Document doc;
				doc.Parse(base64_decode(a["private"].GetString()).c_str());
				if (doc.HasParseError() || !doc["isValid"].GetBool()) continue;

				std::string gameType = doc["queueId"].GetString();
				gameType[0] = toupper(gameType[0]);
				if (strlen(gameType.c_str()) == 0) gameType = "Custom";

				if (doc["isIdle"].GetBool())
					updateActivity("", "Idle", NULL, NULL, EMPTY_IMAGE, "valorant_icon");
				else {
					if (!strcmp(doc["sessionLoopState"].GetString(), "MENUS")) {
						bool isQueue = doc["partyState"].GetString() == "MATCHMAKING";

						if (isQueue && !strcmp(prevState.c_str(), "queue")) timeStart = std::time(0);
						prevState = isQueue ? "queue" : "menu";

						updateActivity(
							std::format("{} ({} of {})", isQueue ? "In Queue" : "In Lobby",
								doc["partySize"].GetInt(),
								doc["maxPartySize"].GetInt()).c_str(),
							gameType.c_str(),
							isQueue ? timeStart : NULL, 
							NULL,
							EMPTY_IMAGE,
							"valorant_icon"
						);
					}
					else {
						std::string map = doc["partyOwnerMatchMap"].GetString();
						size_t lastSlash = map.rfind("/");
						if(lastSlash != std::string::npos) map = map.substr();
						std::string mapAsset(map);
						mapAsset[0] = tolower(mapAsset[0]);
						std::cout << map << std::endl;

						if (!strcmp(doc["sessionLoopState"].GetString(), "PREGAME")) {
							if (!strcmp(prevState.c_str(), "select")) timeStart = std::time(0);
							prevState = "select";

							updateActivity("Agent Select", gameType.c_str(), timeStart, NULL, "valorant_icon", mapAsset.c_str());
						}
						else if (!strcmp(doc["sessionLoopState"].GetString(), "INGAME")) {
							if (!strcmp(prevState.c_str(), "game")) timeStart = std::time(0);
							prevState = "game";

							if (!strcmp(map.c_str(), "Range") || map.empty())
								updateActivity("In Range", "", timeStart, NULL, "valorant_icon", "range");
							else {
								/*std::tm tim = {};
								std::istringstream ss(doc["queueEntryTime"].GetString());
								if (ss >> std::get_time(&tim, "%Y.%m.%d-%H.%M.%S")) {
									time_t now = time(0);
									localtime_s(&tim, &now);
								}
								//else: parsing failed*/

								updateActivity(
									std::format("{} ({} {})",
										gameType,
										doc["partySize"].GetInt(),
										strcmp(gameType.c_str(), "Custom") ? "stack" : std::format("of {}", doc["maxPartySize"].GetInt())
									).c_str(),
									std::format("{} - {}", std::to_string(doc["partyOwnerMatchScoreAllyTeam"].GetInt()), std::to_string(doc["partyOwnerMatchScoreEnemyTeam"].GetInt())).c_str(),
									timeStart,
									NULL,
									"valorant_icon",
									mapAsset.c_str()
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

		printActivity();
		state.core->ActivityManager().ClearActivity([](discord::Result result) {});
		state.core->ActivityManager().UpdateActivity(*(state.activity), [](discord::Result result) {
			std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed") << " updating activity!\n";
		});
	}
}