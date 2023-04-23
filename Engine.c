#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Constants.h"
#include "Environment.h"

void generatePlancton(OceanCell[Y_SIZE][X_SIZE]);
void generateSharks(OceanCell[Y_SIZE][X_SIZE]);
void generateFish(OceanCell ocean[Y_SIZE][X_SIZE]);

void setcur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void fillOcean(OceanCell ocean[Y_SIZE][X_SIZE]) {
	for (int y = 0; y < Y_SIZE; y++) {
		for (int x = 0; x < X_SIZE; x++) {
			ocean[y][x].symbol = SPACE;
			ocean[y][x].alive = EMPTY;
		}
	}
	generatePlancton(ocean);
	generateSharks(ocean);
	generateFish(ocean);
}

void printOcean(OceanCell ocean[Y_SIZE][X_SIZE]) {
	for (int y = 0; y < Y_SIZE; y++) {
		for (int x = 0; x < X_SIZE; x++) {
			if (ocean[y][x].alive == EMPTY) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
			}
			if (ocean[y][x].alive == PLANKTON) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			}
			if (ocean[y][x].alive == FISH) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
			}
			if (ocean[y][x].alive == SHARK) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			}
			printf("%c", ocean[y][x].symbol);
			ocean[y][x].isChecked = 0;
		}

		printf("\n");
	}
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

void updateCell(OceanCell* oldCell, OceanCell* newCell) {

	if (oldCell->alive == PLANKTON) {
		newCell->alive = PLANKTON;
		newCell->isChecked = 1;
		newCell->symbol = PLANKTON_SYMB;
		newCell->plankton.lifeTime = oldCell->plankton.lifeTime;
	}

	if (oldCell->alive == SHARK) {
		if (newCell->alive >= FISH) {
			oldCell->shark.hunger = 0;
		}
		else {
			++oldCell->shark.hunger;
		}
		newCell->alive = SHARK;
		newCell->isChecked = 1;
		newCell->symbol = SHARK_SYMB;
		newCell->shark.hunger = oldCell->shark.hunger;
		newCell->shark.lifeTime = oldCell->shark.lifeTime;
	}

	if (oldCell->alive == FISH) {
		if (newCell->alive == PLANKTON || newCell->alive == FISH) {
			oldCell->fish.hunger = 0;
		}
		else {
			++oldCell->fish.hunger;
		}
		newCell->alive = FISH;
		newCell->isChecked = 1;
		newCell->symbol = FISH_SYMB;
		newCell->fish.hunger = oldCell->fish.hunger;
		newCell->fish.lifeTime = oldCell->fish.lifeTime;
	}
	oldCell->alive = EMPTY;
	oldCell->symbol = SPACE;
}

void checkFishStatus(OceanCell* cell) {

	if (cell->alive == PLANKTON) {
		
	}

	if (cell->alive == SHARK) {
		if (cell->shark.hunger > SHARK_HUNGER || cell->shark.lifeTime > SHARK_LIFETIME) {
			cell->alive = EMPTY;
			cell->symbol = SPACE;
		}
	}

	else if (cell->alive == FISH) {
		if (cell->fish.hunger > FISH_HUNGER || cell->fish.lifeTime > FISH_LIFETIME) {
			cell->alive = EMPTY;
			cell->symbol = SPACE;
		}
	}
	if (cell->alive == PLANKTON) {
		if (cell->plankton.lifeTime > PLANKTON_LIFETIME) {
			cell->alive = EMPTY;
			cell->symbol = SPACE;
		}
	}
}

int makeMoveIfEmpty(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int targ_x, int targ_y, int target) {

	int y_diff = targ_y - curr_y;
	int x_diff = targ_x - curr_x;
	int next_y = curr_y + (y_diff / (abs(y_diff) ? abs(y_diff) : 1));
	int next_x = curr_x + (x_diff / (abs(x_diff) ? abs(x_diff) : 1));

	if (ocean[next_y][next_x].alive <= target) {
		updateCell(&ocean[curr_y][curr_x], &ocean[next_y][next_x]);
		return 1;
	}

	return 0;
}

void randomMovement(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y) {
	while (1) {
		int new_x = curr_x - 1 + rand() % 2;
		int new_y = curr_y - 1 + rand() % 2;
		if (new_x >= 0 && new_x <= X_SIZE && new_y >= 0 && new_y < Y_SIZE) {
			if (ocean[new_y][new_x].alive <= PLANKTON)
			updateCell(&ocean[curr_y][curr_x], &ocean[new_y][new_x]);
			return;
		}
	}
}

int runFromHunter(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int from_x, int from_y, int target) {
	int y_diff = from_y - curr_y;
	int x_diff = from_x - curr_x;
	int next_y = curr_y - (y_diff / (abs(y_diff) ? abs(y_diff) : 1));
	int next_x = curr_x - (x_diff / (abs(x_diff) ? abs(x_diff) : 1));

	
	if (next_x >= 0 && next_x <= X_SIZE && next_y >= 0 && next_y < Y_SIZE) {
		if (ocean[next_y][next_x].alive <= target) {
			updateCell(&ocean[curr_y][curr_x], &ocean[next_y][next_x]);
			return 1;
		}
	}

	return 0;
}

void moveToTheNearestTarget(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int hunter, int target) {
	
	int radius = 1;

	while (curr_x + radius < X_SIZE || curr_y + radius < Y_SIZE || curr_y - radius >= 0 || curr_x - radius >= 0) {

		for (int y = curr_y > radius ? curr_y - radius : 0; y <= curr_y + radius && y < Y_SIZE; y++) {
			for (int x = curr_x > radius ? curr_x - radius : 0; x <= curr_x + radius && x < X_SIZE; x++) {
				if (abs(y - curr_y) != radius && abs(curr_x - x) != radius) {
					x = curr_x + radius - 1;
				}
				else if (ocean[y][x].alive > hunter) {
					if (runFromHunter(ocean, curr_x, curr_y, x, y, target)) {
						return;
					}
				}
				else if (ocean[y][x].alive == target) {
					if (makeMoveIfEmpty(ocean, curr_x, curr_y, x, y, target)) {
						return;
					}
				}
			}
		}

		++radius;
	}

	if (hunter == target) return;
	//moveToTheNearestTarget(ocean, curr_x, curr_y, hunter, hunter);
	randomMovement(ocean, curr_x, curr_y);
}