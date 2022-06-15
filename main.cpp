#include <string>
#include <iostream>
#include <vector>
#include <cstdint>

const int WORLD_SIZE_X = 4;
const int WORLD_SIZE_Y = 3;

const int FINAL_SIZE_X = 2;
const int FINAL_SIZE_Y = 3;

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
	std::vector<item> items; // jakie przedmioty znajduja sie w danej scenie (pokoju)
};

struct player {
	int current_scene_x;
	int current_scene_y;
	std::string name;
	std::vector<item> inventory; // ekwipunek gracza
};

char isValidDirect(std::string input);
void goSomwhere(std::string direction);
void move(int& current_scene_x, int& current_scene_y, char direction);

bool is_game_over();
bool has_player_won(player player);
void display_final_message();
void display_items_in_the_scene(scene scene);
//void pickAnItem(player player, );

int main() {

	// Dane programu:
	scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]; // tablica scen (pokoi) reprezentujaca swiat gry
	player player_1; // zmienna reprezentujaca gracza

	player_1.current_scene_x = 0;
	player_1.current_scene_y = 0;
	scenes[0][0].items = { {"miecz", "",1}, {"tarcza", "", 2}};
	scenes[0][0].description = { "Hello stranger! Are you lost?\n"
							"You just happen to find yourself in a magical labyrinth.\n"
							"Unfortunately, there is only one way to escape. Be careful!\n\n" };

	int state = 0; // obecny stan (patrz: schemat stanów)

	char direction;
	std::string userInput;

	do
	{
		switch (state) // maszyna stanów
		{
		case 0: // stan SCENE
			// wyswietl opis sceny (na podstawie wspolrzednych)
			system("cls");
			std::cout << scenes[player_1.current_scene_x][player_1.current_scene_y].description;
			display_items_in_the_scene(scenes[player_1.current_scene_x][player_1.current_scene_y]);

			//test:
			std::cout << "\ncurrent_scene_x: " << player_1.current_scene_x << "\tcurrent_scene_y: " << player_1.current_scene_y << std::endl;
			// koniec testu
			
			// wystwietl dostepne opcje
			std::cout << "\nWhere you want to go (N)ORTH, (S)OUTH, (E)AST, (W)EST? " << std::endl;

			// zczytaj opcje wybrana przez uzytkownika (walidacja)
			// TODO: Kazdy ma zrobic funkcje walidujaca jego opcje (np. Marcin kierunki, Iza helpa, ja podnies / odloz)
			// ktora zwraca true / false. Sprawdzamy pozniej czy ktorakolwiek zwrocila true, jesli nie to wyswietlamy komunikat
			// (taki ogolny) i zczytujemy dalej
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

		case 3: // state PICK

			// wyswietl dostepne przedmioty
			
			// zapytaj gracza ktory chce podniesc

			// odczytaj odpowiedz (walidacja)

			// jesli nie przekroczymy wagi to przenies do ekwipunku i usun z pokoju (Iza sprawdza ta wage)

			// wroc do stanu SCENE
			state = 0;
			break;

		}

	} while (!has_player_won(player_1));

	return 0;
}

bool is_game_over() {

	return false;
}

bool has_player_won(player player) {

	bool has_player_won = false;

	if (player.current_scene_x == FINAL_SIZE_X && player.current_scene_y == FINAL_SIZE_Y)
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

void display_items_in_the_scene(scene scene) {

	if (scene.items.size() > 0) {

		std::cout << "List of items in the room:" << std::endl;

		for (int i = 0; i < scene.items.size(); i++)
		{
			std::cout << i + 1 <<". " <<scene.items[i].name << " (" <<scene.items[i].weight << "kg)" << std::endl;
		}

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