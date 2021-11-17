#include "discord_handler.h"

//#define DEBUG_UPDATE_ACTIVITY	//Print intermediary debug statements when updating activity
//#define DEBUG_ACTIVITY		//Print debug statements whenever using Discord SDK to update activity

namespace disc {
	namespace {
		volatile bool* interruptFlag;

		time_t timeStart;	//Used to track start of game
		time_t timeAgentSelectEnd; //Track agent select page timing
		std::string inviteLink;

		std::string prevState; //"menu", "queue", "select", "game"
	}


	static void handleDiscordReady(const DiscordUser* connectedUser)
	{
		printf("\nDiscord: connected to user %s#%s - %s\n",
			connectedUser->username,
			connectedUser->discriminator,
			connectedUser->userId);
	}

	static void handleDiscordDisconnected(int errcode, const char* message)
	{
		printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
		*interruptFlag = true;
	}

	static void handleDiscordError(int errcode, const char* message)
	{
		printf("\nDiscord: error (%d: %s)\n", errcode, message);
	}

	void initialize(volatile bool* interrupt) {
		interruptFlag = interrupt;

		DiscordEventHandlers handlers;
		memset(&handlers, 0, sizeof(handlers));
		handlers.ready = handleDiscordReady;
		handlers.disconnected = handleDiscordDisconnected;
		handlers.errored = handleDiscordError;
		Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);

		Discord_Register(APPLICATION_ID, valorantCmd.c_str());

		//Default load-in activity status
		activity.largeImageText = "";
		activity.smallImageText = "";
		activity.type = DISCORD_ACTIVITY_PLAYING;
		disc::updateActivity("", "Loading In...", NULL, NULL, "", "valorant_icon", false);

		Discord_RunCallbacks();
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

				inviteLink = std::format("https://jloh02.github.io/valorant-discord-presence/?party={}&puuid={}&region={}", presenceDoc["partyId"].GetString(), valorant::credentials["puuid"], valorant::credentials["region"]);

				std::string gameType = presenceDoc["queueId"].GetString();
				gameType[0] = toupper(gameType[0]);
				if (strlen(gameType.c_str()) == 0) gameType = "Custom";

				if (presenceDoc["isIdle"].GetBool()) //Idle state
					updateActivity("", "Idle", NULL, NULL, "", "valorant_icon", presenceDoc["partySize"].GetInt() < presenceDoc["maxPartySize"].GetInt());
				else {
					if (!strcmp(presenceDoc["sessionLoopState"].GetString(), "MENUS")) { //In lobby
						bool isQueue = !strcmp(presenceDoc["partyState"].GetString(), "MATCHMAKING");

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
							"valorant_icon",
							presenceDoc["partySize"].GetInt() < presenceDoc["maxPartySize"].GetInt()
						);
					}
					else {
						//Agent select
						if (!strcmp(presenceDoc["sessionLoopState"].GetString(), "PREGAME")) {
							bool firstLoad = strcmp(prevState.c_str(), "select");
							if (firstLoad) valorant::getMatchID(true);
							prevState = "select";

							valorant::GameData gd = valorant::getGameDetails(true);
							time_t updatedTime = std::time(0) + (gd.timeLeft / 1000000000);
							//Only update time when inaccuracy>2s to prevent jittery updates
							if (firstLoad || std::abs(timeAgentSelectEnd - updatedTime >= 2)) timeAgentSelectEnd = updatedTime;

							updateActivity(
								"Agent Select",
								gameType.c_str(),
								NULL,
								timeAgentSelectEnd,
								gd.agentID.empty() ? "valorant_icon" : gd.agentID.c_str(),
								gd.mapID.c_str(),
								presenceDoc["partySize"].GetInt() < presenceDoc["maxPartySize"].GetInt()
							);
						}
						//In game
						else if (!strcmp(presenceDoc["sessionLoopState"].GetString(), "INGAME")) {
							if (strcmp(prevState.c_str(), "game")) {
								valorant::getMatchID(false);
								timeStart = std::time(0);
							}
							prevState = "game";

							valorant::GameData gd = valorant::getGameDetails(false);

							if (!strcmp(presenceDoc["provisioningFlow"].GetString(), "ShootingRange")) //In range
								updateActivity("In Range", "", timeStart, NULL, "valorant_icon", "range", presenceDoc["partySize"].GetInt() < presenceDoc["maxPartySize"].GetInt());
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
									gd.mapID.c_str(),
									presenceDoc["partySize"].GetInt() < presenceDoc["maxPartySize"].GetInt()
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
		writer.String(activity.state);
		writer.String("details");
		writer.String(activity.details);
		writer.String("timestamp");
		writer.StartObject();
		writer.String("start");
		writer.Int64(activity.startTimestamp);
		writer.String("end");
		writer.Int64(activity.endTimestamp);
		writer.EndObject();
		writer.String("assets");
		writer.StartObject();
		writer.String("small");
		writer.String(activity.smallImageKey);
		writer.String("large");
		writer.String(activity.largeImageKey);
		writer.EndObject();
		writer.EndObject();
		std::cout << buffer.GetString() << std::endl;
	}

	void updateActivity(const char* actState, const char* actDetails, time_t startT, time_t endT, const char* smallImg, const char* largeImg, bool inviteAvailable) {
		activity.state = actState;
		activity.details = actDetails;
		activity.startTimestamp = startT;
		activity.endTimestamp = endT;
		activity.smallImageKey = smallImg;
		activity.largeImageKey = largeImg;

		if (inviteAvailable) {
			activity.buttonAlabel = "Request to Join";
			activity.buttonAurl = inviteLink.c_str();
		}
		else {
			activity.buttonAlabel = "";
			activity.buttonAurl = "";
		}

#ifdef DEBUG_ACTIVITY
		printActivity();
#endif

		Discord_UpdatePresence(&activity);
	}
}