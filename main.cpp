#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>


// 
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


std::string is_valid_direct(std::string input);
void go_somwhere(std::string direction);

int main() {

	std::string userInput;

	std::cout << "Where you want to go (N)ORTH, (S)OUTH, (E)AST, (W)EST? " << std::endl;
	std::cin >> userInput;
	go_somwhere(userInput);


	std::fstream newFile;
	newFile.open("game_save.dat", std::ios::out | std::ios::binary);

	if (newFile.is_open()) {
		newFile.write(reinterpret_cast<char*>(&kitchen), sizeof(scene));
		newFile.close();
	}
	else
		std::cout << "ERROR!" << std::endl;

	return 0;
}


/**
* check is input valid
* 	//------- Possible move:
*	//	 North	(N)
*	//	 South	(S)
*	//	 East	(E)
*	//	 West	(W)
*
* @return string with correct  direction or X when input is invalid
*/
std::string is_valid_direct(std::string input) {

	std::string output;

	for (auto& element : input) { element = toupper(element); }

	if (input == "N" || input == "NORTH") { output = "N"; }
	else if (input == "S" || input == "SOUTH") { output = "S"; }
	else if (input == "E" || input == "EAST") { output = "E"; }
	else if (input == "W" || input == "WEST") { output = "W"; }
	else { output = "X"; }

	return output;

}

/**
* function work until user enter valid direction
*
*/
void go_somwhere(std::string direction) {
	while (is_valid_direct(direction) == "X") {
		std::cout << "You choose wrong direction.Try again" << std::endl;
		std::cin >> direction;
	}
	std::cout << "Good move." << std::endl;
}
