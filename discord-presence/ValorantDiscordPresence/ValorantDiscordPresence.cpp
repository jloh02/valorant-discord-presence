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

namespace
{
	volatile bool interrupted{ false };
}

//https://discord.com/developers/docs/game-sdk/sdk-starter-guide#testing-locally-with-two-clients

int main()
{
	if (!server::initialize()) {
		std::cerr << "Unable to find available IP port\n";
		exit(-1);
	}
	std::thread serverThread(server::listenAsync);

	/*
	discord::LobbyTransaction lobby{};
	state.core->LobbyManager().GetLobbyCreateTransaction(&lobby);
	lobby.SetCapacity(2);
	lobby.SetMetadata("foo", "bar");
	lobby.SetMetadata("baz", "bat");
	lobby.SetType(discord::LobbyType::Public);
	state.core->LobbyManager().CreateLobby(
		lobby, [&state](discord::Result result, discord::Lobby const& lobby)
		{
			if (result == discord::Result::Ok)
			{
				std::cout << "Created lobby with secret " << lobby.GetSecret() << "\n";
				std::array<uint8_t, 234> data{};
				state.core->LobbyManager().SendLobbyMessage(
					lobby.GetId(),
					reinterpret_cast<uint8_t*>(data.data()),
					data.size(),
					[](discord::Result result)
					{
						std::cout << "Sent message. Result: " << static_cast<int>(result) << "\n";
					});
			}
			else
			{
				std::cout << "Failed creating lobby. (err " << static_cast<int>(result) << ")\n";
			}
		});
		*/

	disc::initialize();

	while (true);
	/*
	startValorantApplication();
	valorant::initialize();

	std::signal(SIGINT, [](int) { interrupted = true; });

	do {
		if (!valorant::getPresence()) std::cout << "Can't get presence\n"; //continue; //Unable to get presence
		discord::Result cbRes = state.core->RunCallbacks();
		if (cbRes != discord::Result::Ok) //Unable to set presence
			std::cout << "Discord error: " << static_cast<int>(cbRes) << std::endl;
		if (isValorantClosed()) {
			std::cout << "Valorant Application Closed\n";
			interrupted = true;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	} while (!interrupted);

	state.activity.release();
	state.core.release();*/
	server::stop();
}