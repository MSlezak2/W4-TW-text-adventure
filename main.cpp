#include <string>
#include <iostream>

// osobne funkcje do poszczegolnych czynnosci (podnies, uzyj, idz(kierunek), ...)
// HELP ZALEzNY OD OBECNEJ LOkalizacji (np. opis przedmiotow ktore sie tam znajduja)
// warunek zwyciestwa uzaleznic od roznych rzeczy (meta, zebrane przedmioty itd)

struct scene {
	std::string description;
	std::string possible_directions;
	// ... 
};

struct player {
	int current_scene_x;
	int current_scene_y;
	std::string name;
};

char isValidDirect(std::string input);
void goSomwhere(std::string &direction);
void move(int& current_scene_x, int& current_scene_y, char direction);

scene scenes[3][4];

int main() {
	scenes[0][0].possible_directions = "E";
	scenes[0][1].possible_directions = "SEW";
	scenes[0][2].possible_directions = "SEW";
	scenes[0][3].possible_directions = "S";
	scenes[1][0].possible_directions = "NSEW";
	scenes[1][1].possible_directions = "NS";
	scenes[1][2].possible_directions = "N";
	scenes[1][3].possible_directions = "NS";
	scenes[2][0].possible_directions = "NSEW";
	scenes[2][1].possible_directions = "N";
	scenes[2][2].possible_directions = "NSEW";
	scenes[2][3].possible_directions = "N";
	player player_1; // zmienna reprezentujaca gracza
	player_1.current_scene_x = 0;
	player_1.current_scene_y = 0;

	int state = 0; // obecny stan (patrz: schemat stanów)
	std::string userInput;
	char direction;

	do
	{
		switch (state)
		{
		case 0: // stan SCENE

			// wyswietl opis sceny (na podstawie wspolrzednych)
			//std::cout << scenes[player_1.current_scene_x][player_1.current_scene_y].description;
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

	} while (true);

	return 0;
}

/*
	check is input valid
	//------- Possible move:
	//	 North	(N)
	//	 South	(S)
	//	 East	(E)
	//	 West	(W)
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
	}
	std::cout << "Good move." << std::endl;
}
void move(int& current_scene_x, int& current_scene_y, char direction) {
	if (direction == 'N' && (scenes[current_scene_y][current_scene_x].possible_directions.find('N') != std::string::npos)) {
		current_scene_y--;
	}
	else if (direction == 'S' && (scenes[current_scene_y][current_scene_x].possible_directions.find('S') != std::string::npos)) {
		current_scene_y++;
	}
	else if (direction == 'E' && (scenes[current_scene_y][current_scene_x].possible_directions.find('E') != std::string::npos)) {
		current_scene_x++;
	}
	else if (direction == 'W' && (scenes[current_scene_y][current_scene_x].possible_directions.find('W') != std::string::npos)) {
		current_scene_x--;
	}
	else{
		std::cout << "You can't go there!\n";
		return;
	}
}
