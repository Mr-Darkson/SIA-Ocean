#define NOMINMAX
#include "Environment.hpp"
#include "Constants.h"

void generateFish(OceanCell ocean[Y_SIZE][X_SIZE], sf::Sprite fish, sf::Sprite fish1) {
	srand(time(0));
	for (int i = 0; i < FISH_COUNT; ++i) {
		int x = rand() % X_SIZE;
		int y = rand() % Y_SIZE;
		if (ocean[y][x].type != EMPTY) {
			--i;
			continue;
		}

		int sprite = rand() % 2;
		ocean[y][x].type = FISH;
		ocean[y][x].essense.hunger = 0;
		ocean[y][x].essense.gaveBirth = 0;
		ocean[y][x].essense.lifeTime = 0;
		ocean[y][x].sprite = sprite == 0 ? fish : fish1;
	}
}
