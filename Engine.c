#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Constants.h"
#include "Environment.h"

void generatePlancton(OceanCell[Y_SIZE][X_SIZE]);
void generateSharks(OceanCell[Y_SIZE][X_SIZE]);

void setcur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void fillOcean(OceanCell ocean[Y_SIZE][X_SIZE]) {
	for (int y = 0; y < Y_SIZE; y++) {
		for (int x = 0; x < X_SIZE; x++) {
			ocean[y][x].symbol = VOID;
<<<<<<< HEAD
			ocean[y][x].alive = EMPTY;
=======
			ocean[y][x].alive = 0;
>>>>>>> main
		}
	}
	generatePlancton(ocean);
	generateSharks(ocean);
}

void printOcean(OceanCell ocean[Y_SIZE][X_SIZE]) {
	for (int y = 0; y < Y_SIZE; y++) {
		for (int x = 0; x < X_SIZE; x++) {
			printf("%c", ocean[y][x].symbol);
		}

		printf("\n");
	}
<<<<<<< HEAD
=======
}

void setCursor(int state) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);

	if (state == 1) {
		cursorInfo.bVisible = TRUE;
	}
	else cursorInfo.bVisible = FALSE;
	
	SetConsoleCursorInfo(hConsole, &cursorInfo);
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

>>>>>>> main
}