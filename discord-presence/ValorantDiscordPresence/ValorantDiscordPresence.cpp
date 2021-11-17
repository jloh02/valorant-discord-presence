#include <array>
#include <cassert>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <iostream>
#include <thread>
#include <string>
#include <vector>

#include "WIN32_config.h"
#include "utils.h"
#include "discord_handler.h"
#include "riot_api_connection.h"
#include "web_server.h"

#include "discord-rpc/discord_rpc.h"

namespace
{
	volatile bool interrupted{ false };
}

//https://discord.com/developers/docs/game-sdk/sdk-starter-guide#testing-locally-with-two-clients

int main()
{
	std::thread serverThread;
	if (!server::initialize()) {
		std::cerr << "Unable to find available IP port\n";
		popup("Unable to start invitation server. Invite to party functionality may be limited.");
	} else {
		serverThread = std::thread(server::listenAsync);
	}
	
	startValorantApplication();
	disc::initialize(&interrupted);
	valorant::initialize();

	std::signal(SIGINT, [](int) { interrupted = true; });

	do {
		if (!valorant::getPresence()) {
			std::cout << "Can't get presence\n";
			Discord_ClearPresence();
		}

		Discord_RunCallbacks();

		if (isValorantClosed()) {
			std::cout << "Valorant Application Closed\n";
			interrupted = true;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	} while (!interrupted);
	Discord_Shutdown();
	server::stop();
}