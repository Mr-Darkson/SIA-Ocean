#define NOMINMAX
#include <stdlib.h>
#include <time.h>
#include "Constants.h"
#include "Environment.hpp"  

void generatePlancton(OceanCell ocean[Y_SIZE][X_SIZE], sf::Sprite plankton) {
	srand(time(NULL));
	for (int i = 0; i < PLANKTON_COUNT; ++i) {
		int x = rand() % X_SIZE;
		int y = rand() % Y_SIZE;
		if (ocean[y][x].type != EMPTY) {
			--i;
			continue;
		}

		ocean[y][x].type = PLANKTON;
		ocean[y][x].essense.hunger = 0;
		ocean[y][x].essense.gaveBirth = 0;
		ocean[y][x].essense.lifeTime = 0;
		ocean[y][x].sprite = plankton;
		ocean[y][x].sprite.setPosition(x * WINDOW_SIZE_X / X_SIZE, y * WINDOW_SIZE_Y / Y_SIZE);
	}
}