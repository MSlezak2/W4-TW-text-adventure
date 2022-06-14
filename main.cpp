#include <string>
#include <iostream>
#include <vector>

const int final_scene_x = 2;
const int final_scene_y = 3;

// osobne funkcje do poszczegolnych czynnosci (podnies, uzyj, idz(kierunek), ...)
// HELP ZALEzNY OD OBECNEJ LOkalizacji (np. opis przedmiotow ktore sie tam znajduja)
// warunek zwyciestwa uzaleznic od roznych rzeczy (meta, zebrane przedmioty itd)
// przedmiot jako osobna struktura (imie, wage)

struct item {
	std::string name;
	float weight;
};

struct scene {
	std::string description;
	std::string possible_directions[4];
	std::string name;
	// ... 
};

struct player {
	int current_scene_x;
	int current_scene_y;
	std::string name;
};

std::vector<item> inventory;

char isValidDirect(std::string input);
void goSomwhere(std::string direction);
void move(int& current_scene_x, int& current_scene_y, char direction);

scene scenes[3][4];

bool is_game_over();
bool has_player_won(player player);
void display_final_message();

int main() {

	std::cout << "Czolem kluski z rosolem" << std::endl;
	player player_1; // zmienna reprezentujaca gracza
	player_1.current_scene_x = 0;
	player_1.current_scene_y = 0;

	int state = 0; // obecny stan (patrz: schemat stan�w)
	std::string userInput;
	char direction;

	do
	{
		switch (state)
		{
		case 0: // stan SCENE

			// wyswietl opis sceny (na podstawie wspolrzednych)
			std::cout << scenes[player_1.current_scene_x][player_1.current_scene_y].description;
			std::cout << "current_scene_x: " << player_1.current_scene_x << "\tcurrent_scene_y: " << player_1.current_scene_y << std::endl;

			// wystwietl dostepne opcje (na podstawie wspolrzednych)
			std::cout << "Where you want to go (N)ORTH, (S)OUTH, (E)AST, (W)EST? " << std::endl;

			// zczytaj opcje wybrana przez uzytkownika (walidacja)
			std::cin >> userInput;
			goSomwhere(userInput);
			direction = isValidDirect(userInput);

			// zmien stan w zaleznosci od wybranej przez uzytkownika opcji
			state = 1;

			break;

		case 1: // state MOVEMENT

			// zmien wspolzedne 
			move(player_1.current_scene_x, player_1.current_scene_y, direction);

			// wroc do stanu SCENE
			state = 0;
			break;

		}

	} while (!has_player_won(player_1));

	return 0;


	return 0;
}

bool is_game_over() {

	return false;
}

bool has_player_won(player player) {

	bool has_player_won = false;

	if (player.current_scene_x == final_scene_x && player.current_scene_y == final_scene_y)
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
void goSomwhere(std::string direction) {
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