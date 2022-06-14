#include <string>
#include <iostream>

// osobne funkcje do poszczegolnych czynnosci (podnies, uzyj, idz(kierunek), ...)
// HELP ZALEzNY OD OBECNEJ LOkalizacji (np. opis przedmiotow ktore sie tam znajduja)
// warunek zwyciestwa uzaleznic od roznych rzeczy (meta, zebrane przedmioty itd)

struct scene {
	std::string description;
	std::string possible_directions[4];
	// ... 
};

struct player {
	int current_scene_x;
	int current_scene_y;
	std::string name;
};

char isValidDirect(std::string input);
void goSomwhere(std::string direction);
void move(int& current_scene_x, int& current_scene_y, char direction);

scene scenes[2][4];

int main() {

	std::cout << "Czolem kluski z rosolem" << std::endl;
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