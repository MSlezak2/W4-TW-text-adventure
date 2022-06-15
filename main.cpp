#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>



// 
std::string start_room{ "Hello stranger! Are you lost?\n"
							"You just happen to find yourself in a magical labyrinth.\n"
							"Unfortunately, there is only one way to escape. Be careful!\n" };

std::string fairies_room{ "Welcome to the fairies’ room. Do you see these vials?\n "
							"There are 3 elixirs to choose from. Remember, not all fairies are good.\n"
							"You need to trust your intuition.\n" };

std::string snakes_room{ "Oops! There are a lot of snakes!\n"
							"To survive you must choose the right tool to defend yourself.\n" };

std::string dragons_room{ "Oh no! You just woke up the dragon!\n"
							"To calm him down you need to play him a lullaby.\n"
							"There is only one instrument whose sound does not irritate him!\n" };

std::string spiders_room{ "We got you! You have fallen into a huge spider web.\n" };

std::string dwarves_room{ "Good to see you in the dwarves' home -they can help you.\n"
							"However, they won't do it for free!\n" };

std::string vampires_room{ "Do you know what vampires like the most?\n"
							"Give your blood or die...\n " };

std::string monsters_room{ "Have you ever heard about dangerous monsters?\n"
							"This time it's not just a story. Defend yourself!\n" };

std::string end_room{ "Wow, stranger, you are a good one. Congratulations! You are free! \n" };




struct scene {
	//char description[100];
	//char possible_directions[10];
	std::string description;
	std::string possible_directions;
	// ... 
};

struct player {
	int current_scene_x;
	int current_scene_y;
	std::string name;
};


char which_direct(std::string input);
void is_valid_direct(std::string direction);
void to_write(std::string& file_name);
void to_read(std::string& file_name);

int main() {
	player one;
	palyer two;
	std::string userInput;

	std::cout << "Where you want to go (N)ORTH, (S)OUTH, (E)AST, (W)EST? " << std::endl;
	std::cin >> userInput;
	is_valid_direct(userInput);

	system("PAUSE");
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
char which_direct(std::string input) {

	char output;

	for (auto& element : input) { element = toupper(element); }

	if (input == "N" || input == "NORTH") { output = 'N'; }
	else if (input == "S" || input == "SOUTH") { output = 'S'; }
	else if (input == "E" || input == "EAST") { output = 'E'; }
	else if (input == "W" || input == "WEST") { output = 'W'; }
	else { output = 'X'; }


	return output;

}

/**
* function work until user enter valid direction
*
*/
void is_valid_direct(std::string direction) {
	while (which_direct(direction) == 'X') {
		std::cout << "You choose wrong direction.Try again" << std::endl;
		std::cin >> direction;
	}
	std::cout << "Good move." << std::endl;
}

void to_write(std::string& file_name, player& one) {
	std::fstream newFile;

	newFile.open("game_save.dat", std::ios::out | std::ios::binary);

	if (newFile.is_open()) {

		newFile.write(reinterpret_cast<char*>(&one), sizeof(scene));
		newFile.close();
	}
	else
		std::cout << "ERROR!" << std::endl;

}


