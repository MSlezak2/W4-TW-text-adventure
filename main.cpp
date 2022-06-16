#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <conio.h>
#include <algorithm>
#include "game.h"



int main() {

	scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]; // tablica scen (pokoi) reprezentujaca swiat gry
	player player_1; // zmienna reprezentujaca gracza

	loadData(player_1, scenes);

	player_1.currentSceneX = 0;
	player_1.currentSceneY = 0;

	int state = 0; // obecny stan (patrz: schemat stanów)
	int usersChoice;

	do
	{
		switch (state) // maszyna stanów
		{
		case 0: // stan SCENE
		
			system("cls");
			std::cout << scenes[player_1.currentSceneY][player_1.currentSceneX].name << std::endl;
			if (!scenes[player_1.currentSceneY][player_1.currentSceneX].problemSolved)
			{
				std::cout << scenes[player_1.currentSceneY][player_1.currentSceneX].description;
			}
			else
			{
				std::cout << SUCCESS_MESSAGE;
			}

			displayItemsInTheScene(scenes[player_1.currentSceneY][player_1.currentSceneX]);

			if (!hasPlayerWon(player_1))
			{
				state = usersOptions(scenes[player_1.currentSceneY][player_1.currentSceneX]);
			}

			break;

		case 1: // state MOVEMENT

			stateMovement(scenes[player_1.currentSceneY][player_1.currentSceneX], player_1);

			state = 0;
			break;

		case 2: // state INVENTORY

			stateInventory(scenes[player_1.currentSceneY][player_1.currentSceneX], player_1);
		
			state = 0;
			break;

		case 3: // state PICK
		
			statePick(scenes[player_1.currentSceneY][player_1.currentSceneX], player_1, false);

			state = 0;
			break;
		
		
		case 4: // state HELP

			std::string help;

			system("cls");
			actualSceneHelp(player_1.currentSceneX, player_1.currentSceneY, scenes);
			_getch();

			state = 0;
			break;
		}

	} while (!hasPlayerWon(player_1) && state != -1);

	if (state = -1 && !hasPlayerWon(player_1))
	{
		displayGoodByeMessage();
	}

	return 0;
}
