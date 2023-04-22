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

void moveToTheNearestTarget(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, 
	char hunterSymb, int hunter, int target) {

	int radius = 1;

	while (curr_x + radius < X_SIZE || curr_y + radius < Y_SIZE || curr_y - radius >= 0 || curr_x - radius >= 0) {

		if (curr_x + radius < X_SIZE && ocean[curr_y][curr_x + radius].alive == target) {
			ocean[curr_y][curr_x].alive = EMPTY;
			ocean[curr_y][curr_x].symbol = VOID;

			ocean[curr_y][curr_x + 1].alive = hunter;
			ocean[curr_y][curr_x + 1].symbol = hunterSymb;
			break;
		}

		if (curr_x + radius < X_SIZE && curr_y + radius < Y_SIZE && ocean[curr_y + radius][curr_x + radius].alive == target) {
			ocean[curr_y][curr_x].alive = EMPTY;
			ocean[curr_y][curr_x].symbol = VOID;

			ocean[curr_y + 1][curr_x + 1].alive = hunter;
			ocean[curr_y + 1][curr_x + 1].symbol = hunterSymb;
			break;
		}

		if (curr_y + radius < Y_SIZE && ocean[curr_y + radius][curr_x].alive == target) {
			ocean[curr_y][curr_x].alive = EMPTY;
			ocean[curr_y][curr_x].symbol = VOID;

			ocean[curr_y + 1][curr_x].alive = hunter;
			ocean[curr_y + 1][curr_x].symbol = hunterSymb;
			break;
		}

		if (curr_x - radius >= 0 && curr_y + radius < Y_SIZE && ocean[curr_y + radius][curr_x - radius].alive == target) {
			ocean[curr_y][curr_x].alive = EMPTY;
			ocean[curr_y][curr_x].symbol = VOID;

			ocean[curr_y + 1][curr_x - 1].alive = hunter;
			ocean[curr_y + 1][curr_x - 1].symbol = hunterSymb;
			break;
		}

		if (curr_x - radius >= 0 && ocean[curr_y][curr_x - radius].alive == target) {
			ocean[curr_y][curr_x].alive = EMPTY;
			ocean[curr_y][curr_x].symbol = VOID;

			ocean[curr_y][curr_x - 1].alive = hunter;
			ocean[curr_y][curr_x - 1].symbol = hunterSymb;
			break;
		}

		if (curr_x - radius >= 0 && curr_y - radius >= 0 && ocean[curr_y - radius][curr_x - radius].alive == target) {
			ocean[curr_y][curr_x].alive = EMPTY;
			ocean[curr_y][curr_x].symbol = VOID;

			ocean[curr_y - 1][curr_x - 1].alive = hunter;
			ocean[curr_y - 1][curr_x - 1].symbol = hunterSymb;
			break;
		}

		if (curr_y - radius >= 0 && ocean[curr_y - radius][curr_x].alive == target) {
			ocean[curr_y][curr_x].alive = EMPTY;
			ocean[curr_y][curr_x].symbol = VOID;

			ocean[curr_y - 1][curr_x].alive = hunter;
			ocean[curr_y - 1][curr_x].symbol = hunterSymb;
			break;
		}

		if (curr_x + radius < X_SIZE && curr_y - radius >= 0 && ocean[curr_y - radius][curr_x + radius].alive == target) {
			ocean[curr_y][curr_x].alive = EMPTY;
			ocean[curr_y][curr_x].symbol = VOID;

			ocean[curr_y - 1][curr_x + 1].alive = hunter;
			ocean[curr_y - 1][curr_x + 1].symbol = hunterSymb;
			break;
		}

		++radius;
	}

}