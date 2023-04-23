#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Constants.h"
#include "Environment.h"  

void generateFish(OceanCell ocean[Y_SIZE][X_SIZE]) {
	srand(time(NULL));
	for (int i = 0; i < FISH_COUNT; i++) {
		int x = rand() % X_SIZE;
		int y = rand() % Y_SIZE; 

		if (ocean[y][x].alive != EMPTY) {
			i--;
			continue;
		}

		ocean[y][x].fish.lifeTime = 0;
		ocean[y][x].fish.hunger = 0;
		ocean[y][x].fish.gaveBirth = 0;
		ocean[y][x].symbol = FISH_SYMB; //chage cell symbol
		ocean[y][x].alive = FISH; // put fish in cell
	}
}

