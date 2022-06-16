#pragma once

const int WORLD_SIZE_X = 4;
const int WORLD_SIZE_Y = 3;
const int FINAL_SCENE_X = 3;
const int FINAL_SCENE_Y = 2;
const int MAX_WEIGHT = 80;

const std::string SUCCESS_MESSAGE = "Congratulations, you solved all the problems here...\n";

const  std::string HELP = "Every room has its own rules and every item has its own properties. You need to have at least 80 health points to get"
" out of the last room. The weight of the items can not be more than 80. ";

struct item {
	std::string name;
	std::string description;
	int whereToUseX;
	int whereToUseY;
	int weight;
};

struct scene {
	std::string description;
	std::string possibleDirections;
	std::string name;
	bool problemSolved = false;
	std::vector<item> items;
};

struct player {
	int currentSceneX;
	int currentSceneY;
	std::string name;
	std::vector<item> inventory;
	int hp;
};

char isValidDirect(std::string input);
void goSomwhere(std::string& direction);
void move(int& current_scene_x, int& current_scene_y, char direction, scene scene);
bool isGameOver();
bool hasPlayerWon(player player);
void displayGoodByeMessage();
void displayFinalMessage();
int usersOptions(scene scene);
void displayItemsInTheScene(scene scene);
void displayItemsInTheInventory(player player);
void stateMovement(scene scene, player& player);
void statePick(scene& scene, player& player, bool oneOfN);
void stateInventory(scene& scene, player& player);
std::string isHelpNeeded(std::string help);
void actualSceneHelp(int& current_scene_x, int& current_scene_y, scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]);
bool isTooHeavy(player player, item givenItem);
void loadData(player& player, scene scenes[WORLD_SIZE_Y][WORLD_SIZE_X]);

