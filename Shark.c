#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "Constants.h"
#include "Environment.h"

void generateSharks(OceanCell ocean[Y_SIZE][X_SIZE]) {
	for (int i = 0; i < COUNT_SHARKS; ++i) {
		int x = rand() % X_SIZE;
		int y = rand() % Y_SIZE;
		if (ocean[y][x].alive != EMPTY) {
			--i;
			continue;
		}

		ocean[y][x].alive = SHARK;
		Shark shark;
		shark.hunger = 0;
		ocean[y][x].shark = shark;
		ocean[y][x].symbol = SHARK_SYMB;
	}
}