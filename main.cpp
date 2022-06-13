#include <iostream>
#include <cstring>
#include <cctype>
#include<conio.h>
#include <string>
char isValidDirect(std::string input);
void goSomwhere(std::string direction);
void move(int& current_scene_x, int& current_scene_y, char direction);
struct player {
	int current_scene_x;
	int current_scene_y;
	std::string name;
};
int main() {
	player player_1; // player_1 represents a player
	player_1.current_scene_x = 1;
	player_1.current_scene_y = 1;
	std::string userInput;
	std::cout << "Where you want to go (N)ORTH, (S)OUTH, (E)AST, (W)EST? " << std::endl;
	std::cin >> userInput;
	goSomwhere(userInput);
	char direction = isValidDirect(userInput);
	move(player_1.current_scene_x, player_1.current_scene_y, direction);
	std::cout << player_1.current_scene_x << " " << player_1.current_scene_y;
	getch();
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
