#define NOMINMAX
#include <stdlib.h>
#include <time.h>
#include "Constants.h"
#include "Environment.hpp"

void generateSharks(OceanCell ocean[Y_SIZE][X_SIZE], sf::Sprite shark) {
	srand(time(0));
	for (int i = 0; i < COUNT_SHARKS; ++i) {
		int x = rand() % X_SIZE;
		int y = rand() % Y_SIZE;
		if (ocean[y][x].type != EMPTY) {
			--i;
			continue;
		}

		ocean[y][x].type = SHARK;
		ocean[y][x].essense.hunger = 0;
		ocean[y][x].essense.gaveBirth = 0;
		ocean[y][x].essense.lifeTime = 0;
		ocean[y][x].sprite = shark;
	}
}