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
};
	

scene scenes[2][4];

int main() {

	std::cout << "Czolem kluski z rosolem" << std::endl;
	player player_1; // zmienna reprezentujaca gracza
	player_1.current_scene_x = 0;
	player_1.current_scene_y = 0;

	int state = 0; // obecny stan (patrz: schemat stanów)

	do
	{
		switch (state)
		{
		case 0: // stan SCENE

			// wyswietl opis sceny (na podstawie wspolrzednych)
			std::cout << scenes[player_1.current_scene_x][player_1.current_scene_y].description;
			
			// wystwietl dostepne opcje (na podstawie wspolrzednych)

			
			// zczytaj opcje wybrana przez uzytkownika (walidacja)
			// users_choice = let_user_decide();

			// zmien stan w zaleznosci od wybranej przez uzytkownika opcji
			// state = users_choice;
			break;

		case 1: // np. stan NORTH

			// zmniejsz wspolrzedna y o 1
			//player.current_scene_y--;

			// wroc do stanu SCENE
			state = 0;
			break;

		case 2: // np. stan SOUTH

			// zwieksz wspolrzedna y o 1

			// wroc do stanu SCENE
			break;

		}

	} while (false);

	return 0;
}