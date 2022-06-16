#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <conio.h>
#include <algorithm>
#include "game.h"


void stateMovement(scene scene, player& player) {

	char direction;
	std::string userInput;

	if (scene.problemSolved == false && !(player.currentSceneX == 0 && player.currentSceneY == 0) && !(player.currentSceneX == 1 && player.currentSceneY == 0)) {
		system("cls");
		std::cout << "Running away is seldom the right option...\n";
		_getch();
	}
	else {
		system("cls");
		std::cout << "Where you want to go (N)ORTH, (S)OUTH, (E)AST, (W)EST? " << std::endl;

		std::cin >> userInput;
		goSomwhere(userInput);
		direction = isValidDirect(userInput);

		// zmien wspolzedne 
		move(player.currentSceneX, player.currentSceneY, direction, scene);
	}

}

void statePick(scene& scene, player& player, bool oneOfN) {
	// parameter oneOfN determines what happens to items that hasn't been chosen (desappear or remain)

	int usersChoice = 0;
	std::string userInput;

	// wyswietl dostepne przedmioty
	system("cls");
	displayItemsInTheScene(scene);

	// zapytaj gracza ktory chce podniesc
	std::cout << "\nWhich one do you choose?" << std::endl;
	// odczytaj odpowiedz (walidacja)

	while (usersChoice <= 0 || usersChoice > scene.items.size()) {
		std::cin >> userInput;
		try {
			usersChoice = stoi(userInput);
		}
		catch (const std::exception&) {
			std::cout << "Make sure you enter a number from a given range\n";
		}
	}

	if (!isTooHeavy(player, scene.items[usersChoice - 1]))
	{
		player.inventory.push_back(scene.items[usersChoice - 1]);
		std::vector<item>::iterator iterator = scene.items.begin();
		scene.items.erase(iterator + usersChoice - 1);
		if (oneOfN)
		{
			scene.items.clear();
		}
	}
	else {
		std::cout << "\nYour equipment would be too heavy for you to carry. You need make room for that item first...\n";
		_getch();
	}

}

void stateInventory(scene& scene, player& player) {

	char usersChoiceChar = 0;
	int usersChoiceInt = -1;
	std::string userInput;

	// display the content of the inventory
	system("cls");
	displayItemsInTheInventory(player);

	// ask user if he wants to drop something or just come back
	if (player.inventory.size() > 0) {
		std::cout << "\nTo drop something enter 'D', to use one enter 'U', to come back press 'B'\n";

		while (usersChoiceChar != 'D' && usersChoiceChar != 'B' && usersChoiceChar != 'U') {
			std::cin >> userInput;
			usersChoiceChar = userInput.at(0);
			if (usersChoiceChar != 'D' && usersChoiceChar != 'B' && usersChoiceChar != 'U')
			{
				std::cout << "Make sure you enter one of those three options\n";
			}
		}
	}

	// drop an item
	if (usersChoiceChar == 'D')
	{
		// ask which one to drop 
		std::cout << "Which one?\n";
		
		// validate
		while (!(usersChoiceInt > 0 && usersChoiceInt <= player.inventory.size())) {
			std::cin >> userInput;
			try {
				usersChoiceInt = stoi(userInput);
				if (!(usersChoiceInt >= 0 && usersChoiceInt < player.inventory.size()))
				{
					std::cout << "Make sure you enter a number from a given range\n";
				}
			}
			catch (const std::exception&) {
				std::cout << "Make sure you enter a number from a given range\n";
			}
		}
		// drop it
		scene.items.push_back(player.inventory[usersChoiceInt - 1]);
		std::vector<item>::iterator iterator = player.inventory.begin();
		player.inventory.erase(iterator + usersChoiceInt - 1);
	}

	// use item
	if (usersChoiceChar == 'U')
	{
		// ask which one to drop 
		std::cout << "Which one?\n";

		usersChoiceInt = -1;
		// validate
		while (!(usersChoiceInt > 0 && usersChoiceInt <= player.inventory.size())) {
			std::cin >> userInput;
			try {
				usersChoiceInt = stoi(userInput);
				if (!(usersChoiceInt >= 0 && usersChoiceInt < player.inventory.size()))
				{
					std::cout << "Make sure you enter a number from a given range\n";
				}
			}
			catch (const std::exception&) {
				std::cout << "Make sure you enter a number from a given range\n";
			}
		}
		// use it
		if (player.currentSceneX == player.inventory[usersChoiceInt - 1].whereToUseX && player.currentSceneY == player.inventory[usersChoiceInt - 1].whereToUseY) {
			scene.problemSolved = true;
		}
		else {
			system("cls");
			std::cout << "Unfortunatelly, you can't use that in here. Try something else\n";
			_getch();
		}
	}
}

bool isGameOver() {

	return false;
}

bool hasPlayerWon(player player) {

	bool has_player_won = false;

	if (player.currentSceneX == FINAL_SCENE_X && player.currentSceneY == FINAL_SCENE_Y)
	{
		has_player_won = true;
		displayFinalMessage();
	}

	return has_player_won;
}

void displayGoodByeMessage() {
	system("cls");
	std::cout << "Ufff... It was just a dream after all\n";
	_getch();
}

void displayFinalMessage() {

	system("cls");
	std::cout << "Congratulation! You've made it after all!\n";
	_getch();
}

int usersOptions(scene scene) {

	int state = -2;
	int i = 0;
	std::string users_input;

	// display options:
	std::cout << "\nWhat's your choice?" << std::endl;
	std::cout << ++i << ". MOVE" << std::endl;
	std::cout << ++i << ". TAKE A LOOKA AT THE INVENTORY" << std::endl;
	if (scene.items.size() > 0)
	{
		std::cout << ++i << ". PICK AN ITEM" << std::endl;
	}
	std::cout << "(h)elp" << ". ASK GENIE FOR HELP" << std::endl;
	std::cout << "e(x)it" << ". WAKE UP (EXIT THE GAME)" << std::endl;

	// validate user's input
	while (state != -1 && state != 4 && !(state >= 0 && state <= i) ) {

		std::cin >> users_input;
		std::transform(users_input.begin(), users_input.end(), users_input.begin(), ::toupper);

		if (users_input.compare("HELP") == 0 || users_input.compare("H") == 0) {
			state = 4; //state HELP
		}
		else if (users_input.compare("EXIT") == 0 || users_input.compare("X") == 0) {
			state = -1; //break the main loop (and exit the game)
		}
		else {
			try {
				state = stoi(users_input);

			}
			catch (const std::exception&) {
				system("cls");
				std::cout << "Make sure you enter the right thing";
				_getch();
				state = 0;
			}
		}

	}

	// redirect to appropriate state
	return state;
}

void displayItemsInTheScene(scene scene) {

	if (scene.items.size() > 0) {

		std::cout << "List of items in the room:" << std::endl;

		for (int i = 0; i < scene.items.size(); i++)
		{
			std::cout << i + 1 << ". " << scene.items[i].name << " (" << scene.items[i].weight << "kg)" << std::endl;
		}

	}

}

void displayItemsInTheInventory(player player) {

	if (player.inventory.size() > 0) {

		std::cout << "Your inventory:" << std::endl;

		for (int i = 0; i < player.inventory.size(); i++)
		{
			std::cout << i + 1 << ". " << player.inventory[i].name << " (" << player.inventory[i].weight << "kg)" << std::endl;
		}

	}
	else {
		std::cout << "Looks like it's empty";
		_getch();
	}

}

/*

 @return string with correct  direction or X when input is invalid
*/
char isValidDirect(std::string input) {
	char output;
	for (auto& element : input) { element = toupper(element); }
	// TODO: Repair reading of mixed case words 
	if (input == "N" || input == "NORTH") { output = 'N'; }
	else if (input == "S" || input == "SOUTH") { output = 'S'; }
	else if (input == "E" || input == "EAST") { output = 'E'; }
	else if (input == "W" || input == "WEST") { output = 'W'; }
	else { output = 'X'; }
	return output;
}
// function works until user enters valid direction
void goSomwhere(std::string& direction) {
	while (isValidDirect(direction) == 'X') {
		std::cout << "You have chosen wrong direction. Try again" << std::endl;
		std::cin >> direction;
	}
}
void move(int& current_scene_x, int& current_scene_y, char direction, scene scene) {
	if (direction == 'N' && (scene.possibleDirections.find('N') != std::string::npos)) {
		current_scene_y--;
	}
	else if (direction == 'S' && (scene.possibleDirections.find('S') != std::string::npos)) {
		current_scene_y++;
	}
	else if (direction == 'E' && (scene.possibleDirections.find('E') != std::string::npos)) {
		current_scene_x++;
	}
	else if (direction == 'W' && (scene.possibleDirections.find('W') != std::string::npos)) {
		current_scene_x--;
	}
	else {
		std::cout << "You can't go there!\n";
		_getch();
		return;
	}
}

std::string isHelpNeeded(std::string help) {
	do
	{
		help.clear();
		std::cout << "Type HELP or H to get help\n";
		(std::cin >> help).get();
		std::transform(help.begin(), help.end(), help.begin(), toupper);
		std::cout << " ";

	} while (help != "HELP" && help != "H");

	return help;
}

void actualSceneHelp(int& current_scene_x, int& current_scene_y, scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]) {


	std::cout << HELP << std::endl;
	for (int i = 0; i < scenes[current_scene_y][current_scene_x].items.size(); i++) {
		std::cout << scenes[current_scene_y][current_scene_x].items[i].name << "  ";
		std::cout << scenes[current_scene_y][current_scene_x].items[i].description << "   ";
		std::cout << scenes[current_scene_y][current_scene_x].items[i].weight << "   ";
		std::cout << "\n";

	}


}

bool isTooHeavy(player player, item given_item) {

	bool isTooHeavy = false;

	int itemWeight = given_item.weight;
	std::vector<item> equipment = player.inventory;

	int equipmentWeight = 0;

	for (int i = 0; i < equipment.size(); i++)
	{
		equipmentWeight += equipment[i].weight;
	}

	if (itemWeight + equipmentWeight > MAX_WEIGHT)
	{
		isTooHeavy = true;
	}

	return isTooHeavy;
}

void loadData(player& player, scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]) {

	scenes[0][0].name = "START";
	scenes[0][0].items = {};
	scenes[0][0].problemSolved = false;
	scenes[0][0].description = { "Hello stranger! Are you lost?\n"
							"You just happen to find yourself in a magical labyrinth.\n"
							"Unfortunately, there is only one way to escape. Be careful!\n\n" };

	scenes[0][1].name = { "FAIRIES’ ROOM \n" };
	scenes[0][1].problemSolved = false;
	scenes[0][1].items = { {"red elixir", "allows to break free from a certain room", 1, 2, 40},
						{"blue elixir", "allows to open a certain door", 3, 1, 40},
						{"green elixir", "allows to open a certain door", 3, 0, 40} };

	scenes[0][1].description = { "Welcome to the fairies’ room. Do you see these vials?\n"
							"There are 3 elixirs to choose from. Remember, not all fairies are good. \n"
							"You need to trust your intuition." };

	scenes[0][2].name = { "SNAKES’ ROOM \n" };
	scenes[0][2].items = { {" arc ", "to use it you need to leave one item and you are going to lose your health points", 2, 0, 30},
							{"spear", "to use it you need to leave 2 items", 2, 0, 20},
						{"magic liquid", "allows to open a certain door", 2, 0, 40} };

	scenes[0][2].description = { "Oops! There are a lot of snakes! \n"
							"To survive you must choose the right tool to defend yourself.\n\n" };

	scenes[0][3].name = { "DRAGONS’ ROOM\n" };
	scenes[0][3].items = { {"flute", "you need to leave one item", 3, 0, 20},
							{"spear", "to use it you need to leave 2 items", 3, 0, 30} };

	scenes[0][3].description = { "Oh no! You just woke up the dragon! To calm him down you need to play him a lullaby.  \n"
							"There is only one instrument whose sound does not irritate him!\n\n" };


	scenes[1][0].items = { };

	scenes[1][0].description = { };

	scenes[1][1].name = { "SPIDERS’ ROOM\n" };
	scenes[1][1].items = { {"freezing power ", "you are going to lose your health points  - 40", 1, 1, 20},
							{"flute", "you need to leave one item", 1, 1, 20},
							{"gas", "you need to leave one item and you are going to lose your health points-10", 1, 1, 20} };

	scenes[1][1].description = { "We got you! You have fallen into a huge spider web.!\n\n" };

	scenes[1][2].name = { "DWARVES ROOM\n" };
	scenes[1][2].items = { {"healing pill", "adding 80 health points but you need to leave 2 items", 2, 1, 20},
							{"bangade", "adding 50 health points but you need to leave one item", 2, 1, 20},
							{"magic liquid", "leave here magic liquid and you are going to get 50 health points", 2, 1, 20} };

	scenes[1][2].description = { "Good to see you in the dwarves' home -they can help you.\n"
								"However, they won't do it for free!!\n\n" };

	scenes[1][3].name = { "VAMPIRES’ ROOM\n" };
	scenes[1][3].items = { {"syringe", "alive but you will lose your power -50:)", 3, 1, 20},
							{"arc", "to use it you need to leave one item and you are going to lose your health points -10) ", 3, 1, 20}};

	scenes[1][3].description = { "Do you know what vampires like the most ? Give your blood or die.\n\n" };


	scenes[2][0].items = { };
	scenes[2][0].description = { };

	scenes[2][1].name = { "MONSTERS’ ROOM \n" };
	scenes[2][1].items = { {"silver sword ", "you need to leave one item and you are going to lose your health points-30)", 1, 2, 30},
							{"violin", "you are going to lose your health points-40)) ", 1, 2, 30} };

	scenes[2][1].description = { "Have you ever heard about dangerous monsters?\n"
								"This time it's not just a story. Defend yourself!\n\n" };


	scenes[2][2].items = { };
	scenes[2][2].description = { };

	scenes[2][3].name = { "THE END\n" };
	scenes[2][3].items = { };
	scenes[2][3].description = { "Wow, stranger, you are a good one. Congratulations! You are free!!\n\n" };


	scenes[0][0].possibleDirections = "E";
	scenes[0][1].possibleDirections = "SEW";
	scenes[0][2].possibleDirections = "SEW";
	scenes[0][3].possibleDirections = "S";
	scenes[1][0].possibleDirections = "NSEW";
	scenes[1][1].possibleDirections = "NS";
	scenes[1][2].possibleDirections = "N";
	scenes[1][3].possibleDirections = "NS";
	scenes[2][0].possibleDirections = "NSEW";
	scenes[2][1].possibleDirections = "N";
	scenes[2][2].possibleDirections = "NSEW";
	scenes[2][3].possibleDirections = "N";
}

