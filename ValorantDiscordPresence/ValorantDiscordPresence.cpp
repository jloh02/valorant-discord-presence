#include <array>
#include <cassert>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <format>
#include <string>

#include "WIN32_config.h"
#include "utils.h"
#include "discord_handler.h"
#include "riot_api_connection.h"

namespace
{
	volatile bool interrupted{ false };
}

//https://discord.com/developers/docs/game-sdk/sdk-starter-guide#testing-locally-with-two-clients

int main(int, char** argv)
{
	disc::initialize();
	startValorantApplication();
	
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
	
	
	valorant::initialize(); //WSS callback handles ending of application to prevent infinite while loop

	while (true) {
		valorant::getPresence();
		state.core->RunCallbacks();
		std::this_thread::sleep_for(std::chrono::seconds(15));
	}
}
