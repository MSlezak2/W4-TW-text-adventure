#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <conio.h>
#include <algorithm>

const int WORLD_SIZE_X = 4;
const int WORLD_SIZE_Y = 3;

const int FINAL_SCENE_X = 2;
const int FINAL_SCENE_Y = 3;

const int MAX_WEIGHT = 80;

// osobne funkcje do poszczegolnych czynnosci (podnies, uzyj, idz(kierunek), ...)
// HELP ZALEzNY OD OBECNEJ LOkalizacji (np. opis przedmiotow ktore sie tam znajduja)
// warunek zwyciestwa uzaleznic od roznych rzeczy (meta, zebrane przedmioty itd)
// przedmiot jako osobna struktura (imie, wage)

struct item {
	std::string name;
	std::string description;
	int weight;
};

struct scene {
	std::string description;
	std::string possible_directions[4];
	std::string name;
	std::string help;
	std::vector<item> items; // jakie przedmioty znajduja sie w danej scenie (pokoju)
};

struct player {
	int current_scene_x;
	int current_scene_y;
	std::string name;
	std::vector<item> inventory; // ekwipunek gracza
	int hp;
};
	
char isValidDirect(std::string input);
void goSomwhere(std::string &direction);
void move(int& current_scene_x, int& current_scene_y, char direction);

bool is_game_over();
bool has_player_won(player player);
void display_final_message();

int users_options(scene scene);
void display_items_in_the_scene(scene scene);
void display_items_in_the_inventory(player player);
//void pickAnItem(player player, );

void state_movement(player &player);
void state_pick(scene &scene, player &player, bool oneOfN);
void state_inventory(scene &scene, player &player);

std::string isHelpNeeded(std::string help);
void actualSceneHelp(int& current_scene_x, int& current_scene_y, scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]);
bool isTooHeavy(player player, item givenItem);
void loadData(player &player, scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]);

int main() {



	// Dane programu:
	scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]; // tablica scen (pokoi) reprezentujaca swiat gry
	player player_1; // zmienna reprezentujaca gracza

	loadData(player_1, scenes);

	player_1.current_scene_x = 0;
	player_1.current_scene_y = 0;
	//scenes[0][0].items = {{"miecz", ""/*,1*/}, {"tarcza", ""/*, 2*/}};
	//scenes[0][0].help = "help";
	//scenes[0][0].description = { "Hello stranger! Are you lost?\n"
	//						"You just happen to find yourself in a magical labyrinth.\n"
	//						"Unfortunately, there is only one way to escape. Be careful!\n\n" };

	int state = 0; // obecny stan (patrz: schemat stanów)

	int usersChoice;

	do
	{
		switch (state) // maszyna stanów
		{
		case 0: // stan SCENE
			// wyswietl opis sceny (na podstawie wspolrzednych)
			system("cls");
			std::cout << scenes[player_1.current_scene_y][player_1.current_scene_x].description;
			display_items_in_the_scene(scenes[player_1.current_scene_y][player_1.current_scene_x]);

			//test:
			std::cout << "\ncurrent_scene_x: " << player_1.current_scene_x << "\tcurrent_scene_y: " << player_1.current_scene_y << std::endl;
			// koniec testu

			// zczytaj opcje wybrana przez uzytkownika (walidacja)
			// TODO: Kazdy ma zrobic funkcje walidujaca jego opcje (np. Marcin kierunki, Iza helpa, ja podnies / odloz)
			// ktora zwraca true / false. Sprawdzamy pozniej czy ktorakolwiek zwrocila true, jesli nie to wyswietlamy komunikat
			// (taki ogolny) i zczytujemy dalej

			// zmien stan w zaleznosci od wybranej przez uzytkownika opcji
			state = users_options(scenes[player_1.current_scene_y][player_1.current_scene_x]);

			break;

		case 1: // state MOVEMENT

			state_movement(player_1);

			// wroc do stanu SCENE
			state = 0;
			break;

		case 2: // state INVENTORY

			state_inventory(scenes[player_1.current_scene_y][player_1.current_scene_y], player_1);
			// wroc do stanu SCENE
			state = 0;
			break;

		case 3: // state PICK
		{

			state_pick(scenes[player_1.current_scene_y][player_1.current_scene_x], player_1, false);

			// wroc do stanu SCENE
			state = 0;
			break;
		}
		
		case 4: // state HELP

			std::string help;

			//isHelpNeeded(help);
			system("cls");
			actualSceneHelp(player_1.current_scene_x, player_1.current_scene_y, scenes);
			_getch();

			// wroc do stanu SCENE
			state = 0;
			break;
		}

	} while (!has_player_won(player_1) && state != -1);

	if (state = -1)
	{
		system("cls");
		std::cout << "\nUfff... It was just a dream after all\n";
	}

	return 0;
}

void state_movement(player &player) {

	char direction;
	std::string userInput;

	system("cls");
	std::cout << "\nWhere you want to go (N)ORTH, (S)OUTH, (E)AST, (W)EST? " << std::endl;

	std::cin >> userInput;
	goSomwhere(userInput);
	direction = isValidDirect(userInput);

	// zmien wspolzedne 
	move(player.current_scene_x, player.current_scene_y, direction);
}

void state_pick(scene &scene, player &player, bool oneOfN) {
	// parameter oneOfN determines what happens to items that hasn't been chosen (desappear or remain)

	int usersChoice = 0;
	std::string userInput;

	// wyswietl dostepne przedmioty
	system("cls");
	display_items_in_the_scene(scene);

	// zapytaj gracza ktory chce podniesc
	std::cout << "\nWhich one do you choose?" << std::endl;
	// odczytaj odpowiedz (walidacja)
	
	while (usersChoice == 0) {
		std::cin >> userInput;
		try {
			usersChoice = stoi(userInput);
		}
		catch (const std::exception&) {
			std::cout << "Make sure you enter a number from a given range\n";
		}
	}

	// jesli nie przekroczymy wagi to przenies do ekwipunku i usun z pokoju (Iza sprawdza ta wage)
	if (!isTooHeavy(player, scene.items[usersChoice - 1] ))
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

void state_inventory(scene& scene, player& player) {
	
	char usersChoiceChar = 0;
	int usersChoiceInt = -1;
	std::string userInput;

	// display the content of the inventory
	system("cls");
	display_items_in_the_inventory(player);
	
	// ask user if he wants to drop something or just come back
	if (player.inventory.size() > 0) {
		std::cout << "\nTo drop something enter 'D', to come back press 'B'\n";

		while (usersChoiceChar != 'D' && usersChoiceChar != 'B') {
			std::cin >> userInput;
			usersChoiceChar = userInput.at(0);
			if (usersChoiceChar != 'D' && usersChoiceChar != 'B')
			{
				std::cout << "Make sure you enter one of those two options\n";
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

}

bool is_game_over() {

	return false;
}

bool has_player_won(player player) {

	bool has_player_won = false;

	if (player.current_scene_x == FINAL_SCENE_X && player.current_scene_y == FINAL_SCENE_Y)
	{
		has_player_won = true;
		display_final_message();
	}

	return has_player_won;
}

void display_final_message() {

	system("cls");

	std::cout << "Congratulation! You've made it after all!";
}

int users_options(scene scene) {

	int state = -2;
	int i = 0;
	std::string users_input;

	// display options:
	std::cout << "\nWhat's your choice?" <<std::endl;
	std::cout << ++i <<". MOVE" << std::endl;
	std::cout << ++i << ". TAKE A LOOKA AT THE INVENTORY" << std::endl;
	if (scene.items.size() > 0)
	{
		std::cout << ++i << ". PICK AN ITEM" << std::endl;
	}
	std::cout << "(h)elp" << ". ASK GENIE FOR HELP" << std::endl;
	std::cout << "e(x)it" << ". WAKE UP (EXIT THE GAME)" << std::endl;

	// validate user's input
	while (state == -2) {

		std::cin >> users_input;
		std::transform(users_input.begin(), users_input.end(), users_input.begin(), ::toupper);

		if (users_input.compare("HELP") == 0 || users_input.compare("H") == 0){
			state = 4; //state HELP
		}
		else if (users_input.compare("EXIT") == 0 || users_input.compare("X") == 0){
			state = -1; //break the main loop (and exit the game)
		}
		else{
			try{
				state = stoi(users_input);

			}
			catch (const std::exception&){
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

void display_items_in_the_scene(scene scene) {

	if (scene.items.size() > 0) {

		std::cout << "List of items in the room:" << std::endl;

		for (int i = 0; i < scene.items.size(); i++)
		{
			std::cout << i + 1 <<". " <<scene.items[i].name /* << " (" << scene.items[i].weight << "kg)" */ << std::endl;
		}

	}

}

void display_items_in_the_inventory(player player) {

	if (player.inventory.size() > 0) {

		std::cout << "Your inventory:" << std::endl;

		for (int i = 0; i < player.inventory.size(); i++)
		{
			std::cout << i + 1 << ". " << player.inventory[i].name /* << " (" << player.inventory[i].weight << "kg)" */ << std::endl;
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
void goSomwhere(std::string &direction) {
	while (isValidDirect(direction) == 'X') {
		std::cout << "You have chosen wrong direction. Try again" << std::endl;
		std::cin >> direction;
		isValidDirect(direction);
	}
	std::cout << "Good move." << std::endl;
}
void move(int& current_scene_x, int& current_scene_y, char direction) {
	if (direction == 'N'/* && scene???.possible_directions.find("N")<4*/) {
		current_scene_y--;
	}
	if (direction == 'S') {
		current_scene_y++;
	}
	if (direction == 'E') {
		current_scene_x++;
	}
	if (direction == 'W') {
		current_scene_x--;
	}
}

std::string isHelpNeeded(std::string help){
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

void actualSceneHelp(int& current_scene_x, int& current_scene_y, scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]){

	//std::string actualHelp;
	//actualHelp = scenes[current_scene_x][current_scene_y].help;
	//std::cout << actualHelp;
 
	// wyswietl wspolnego helpa

	// wyswietl liste przedmiotow z ich nazwa opisem i waga

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

		scenes[0][0].items = {};
		scenes[0][0].description = { "Hello stranger! Are you lost?\n"
								"You just happen to find yourself in a magical labyrinth.\n"
								"Unfortunately, there is only one way to escape. Be careful!\n\n" };

		scenes[0][1].items = { {"red elixir", "allows to break free from a certain room", 40},
							{"blue elixir" "allows to open a certain door", 40},
							{"green elixir " "allows to open a certain door", 40} };

		scenes[0][1].description = { "Welcome to the fairies’ room. Do you see these vials?\n"
								"There are 3 elixirs to choose from. Remember, not all fairies are good. \n"
								"You need to trust your intuition." };


		scenes[0][2].items = { {" arc ", "to use it you need to leave one item and you are going to lose your health points",30},
								{"spear", "to use it you need to leave 2 items", 20},
							{"magic liquid", "allows to open a certain door", 40} };

		scenes[0][2].description = { "Oops! There are a lot of snakes! \n"
								"To survive you must choose the right tool to defend yourself.\n\n" };

		scenes[0][3].items = { {"flute", "you need to leave one item",20},
								{"spear", "to use it you need to leave 2 items", 30},
							{"green elixir", "you can use here a  green elixir and continue the game without losing your health points", 40} };

		scenes[0][3].description = { "Oh no! You just woke up the dragon! To calm him down you need to play him a lullaby.  \n"
								"There is only one instrument whose sound does not irritate him!\n\n" };


		scenes[1][0].items = { };

		scenes[1][0].description = { };

		scenes[1][1].items = { {"freezing power ", "you are going to lose your health points  - 40",20},
								{"flute", "you need to leave one item", 20},
								{"gas", "you need to leave one item and you are going to lose your health points-10", 20} };

		scenes[1][1].description = { "We got you! You have fallen into a huge spider web.!\n\n" };


		scenes[1][2].items = { {"healing pill", "adding 80 health points but you need to leave 2 items",20},
								{"bangade", "adding 50 health points but you need to leave one item", 20},
								{"magic liquid", "leave here magic liquid and you are going to get 50 health points", 20} };

		scenes[1][2].description = { "Good to see you in the dwarves' home -they can help you.\n"
									"However, they won't do it for free!!\n\n" };

		scenes[1][3].items = { {"syringe", "alive but you will lose your power -50:)",20},
								{"arc", "to use it you need to leave one item and you are going to lose your health points -10) ", 20},
								{"blue elixir", "you can use here a blue elixir to go out  from labyrinth", 20} };

		scenes[1][3].description = { "Do you know what vampires like the most ? Give your blood or die.\n\n" };


		scenes[3][0].items = { };
		scenes[3][0].description = { };

		scenes[3][1].items = { {"silver sword ", "you need to leave one item and you are going to lose your health points-30)",30},
								{"violin", "you are going to lose your health points-40)) ", 30},
								{"red elixir ", "you can use here a red elixir and go out without losing your health points", 20} };

		scenes[3][1].description = { "Have you ever heard about dangerous monsters?\n"
									"This time it's not just a story. Defend yourself!\n\n" };

		scenes[3][2].items = { };
		scenes[3][2].description = { };

		scenes[3][3].items = { };
		scenes[3][2].description = { "Wow, stranger, you are a good one. Congratulations! You are free!!\n\n" };

}