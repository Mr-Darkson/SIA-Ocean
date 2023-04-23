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
		ocean[y][x].plankton.lifeTime = 10;
	}
}

void bornPlankton(OceanCell ocean[X_SIZE][Y_SIZE], int y, int x) {
	ocean[y][x].alive = 1;
	ocean[y][x].plankton.lifeTime = 10;
	ocean[y][x].symbol = PLANKTON_SYMB;
	return;
}

void traxPlancton(OceanCell ocean[X_SIZE][Y_SIZE], int y, int x) {
		srand(time(NULL));
		int random = rand() % 2;
		if (random == 0) { 
			if ((x - 1 >= 0) && (ocean[y][x-1].alive == 0)) bornPlankton(ocean, x - 1, y);
			else if((x + 1 < X_SIZE) && (ocean[y][x + 1].alive == 0))bornPlankton(ocean, x + 1, y);
			else if((y - 1 >= 0) && (ocean[y-1][x].alive == 0))bornPlankton(ocean, x, y - 1);
			else if((y + 1 < Y_SIZE) && (ocean[y + 1][x].alive == 0))bornPlankton(ocean, x, y + 1);
		}
		else {
			if ((y - 1 >= 0) && (ocean[y - 1][x].alive == 0))bornPlankton(ocean, x, y - 1);
			else if ((y + 1 < Y_SIZE) && (ocean[y + 1][x].alive == 0))bornPlankton(ocean, x, y + 1);
			else if ((x - 1 >= 0) && (ocean[y][x - 1].alive == 0)) bornPlankton(ocean, x - 1, y);
			else if ((x + 1 < X_SIZE) && (ocean[y][x + 1].alive == 0))bornPlankton(ocean, x + 1, y);
		}
		
	return;
}

void diedPlankton(OceanCell ocean[X_SIZE][Y_SIZE], int x, int y) {
	ocean[y][x].alive = 0;
	ocean[y][x].symbol = ' ';
}