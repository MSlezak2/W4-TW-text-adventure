#include <iostream>
#include <cstring>
#include <cctype>


std::string isValidDirect(std::string input);
void goSomwhere(std::string direction);

int main() {

	std::string userInput;

	std::cout << "Where you want to go (N)ORTH, (S)OUTH, (E)AST, (W)EST? " << std::endl;
	std::cin >> userInput;
	goSomwhere(userInput);


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
std::string isValidDirect(std::string input) {

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
void goSomwhere(std::string direction) {
	while (isValidDirect(direction) == "X") {
		std::cout << "You choose wrong direction.Try again" << std::endl;
		std::cin >> direction;
		isValidDirect(direction);
	}
	std::cout << "Good move." << std::endl;
}
