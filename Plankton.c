#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Constants.h"
#include "Environment.h"  

void generatePlancton(OceanCell ocean[Y_SIZE][X_SIZE]) {
	srand(time(NULL));
	for (int i = 0; i < PLANKTON_COUNT; i++) {
		int x = rand() % X_SIZE;
		int y = rand() % Y_SIZE;
		if (ocean[y][x].symbol != ' ') {
			i--;
			continue;
		}
		ocean[y][x].symbol = PLANKTON_SYMB; //change cell symbol
		ocean[y][x].alive = PLANKTON; // put fish in cell
		ocean[y][x].plankton.lifeTime = PLANKTON_LIFETIME;
	}
	
}