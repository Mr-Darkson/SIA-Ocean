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
			ocean[y][x].symbol = SPACE;
			ocean[y][x].alive = 0;
		}
	}
	generatePlancton(ocean);
	generateSharks(ocean);
}

void printOcean(OceanCell ocean[Y_SIZE][X_SIZE]) {
	for (int y = 0; y < Y_SIZE; y++) {
		for (int x = 0; x < X_SIZE; x++) {
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
	if (oldCell->alive == SHARK) {
		if (newCell->alive != EMPTY) {
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
		//*newCell = *oldCell;
	}
	oldCell->alive = EMPTY;
	oldCell->symbol = SPACE;
	//add fish
}

void checkFishStatus(OceanCell* cell) {
	if (cell->alive == SHARK) {
		if (cell->shark.hunger > SHARK_HUNGER || cell->shark.lifeTime > SHARK_LIFETIME) {
			cell->alive = EMPTY;
			cell->symbol = SPACE;
		}
	}
	//add fish
}

void moveToTheNearestTarget(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int hunter, int target) {
	
	int radius = 1;

	while (curr_x + radius < X_SIZE || curr_y + radius < Y_SIZE || curr_y - radius >= 0 || curr_x - radius >= 0) {

		int x = curr_x - radius;
		int y = curr_y - radius;
		for (; x <= curr_x + radius; x++) {
			if (x < 0 || x >= X_SIZE || y < 0) {
				continue;
			}

			if (ocean[y][x].alive == target) {

				if (x < curr_x && ocean[curr_y - 1][curr_x - 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y - 1][curr_x - 1]);
					return;
				}

				if (x > curr_x && ocean[curr_y - 1][curr_x + 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y - 1][curr_x + 1]);
					return;
				}

				if (x == curr_x && ocean[curr_y - 1][curr_x].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y - 1][curr_x]);
					return;
				}
			}

		}
		--x;

		for (; y <= curr_y + radius; y++) {
			if (y < 0 || y >= Y_SIZE || x >= X_SIZE) {
				continue;
			}

			if (ocean[y][x].alive == target) {

				if (y < curr_y && ocean[curr_y - 1][curr_x + 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y - 1][curr_x + 1]);
					return;
				}

				if (y > curr_y && ocean[curr_y + 1][curr_x + 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y + 1][curr_x + 1]);
					return;
				}

				if (y == curr_x && ocean[curr_y][curr_x + 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y][curr_x + 1]);
					return;
				}
			}

		}
		--y;

		for (; x >= curr_x - radius; x--) {
			if (y >= Y_SIZE || x < 0 || x >= X_SIZE) {
				continue;
			}

			if (ocean[y][x].alive == target) {

				if (x < curr_x && ocean[curr_y + 1][curr_x - 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y + 1][curr_x - 1]);
					return;
				}

				if (x > curr_x && ocean[curr_y + 1][curr_x + 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y + 1][curr_x + 1]);
					return;
				}

				if (x == curr_x && ocean[curr_y + 1][curr_x].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y + 1][curr_x]);
					return;
				}
			}

		}
		++x;

		for (; y >= curr_y - radius; y--) {
			if (y < 0 || y >= Y_SIZE || x < 0) {
				continue;
			}

			if (ocean[y][x].alive == target) {

				if (y < curr_y && ocean[curr_y - 1][curr_x - 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y - 1][curr_x - 1]);
					return;
				}

				if (y > curr_y && ocean[curr_y + 1][curr_x - 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y + 1][curr_x - 1]);
					return;
				}

				if (y == curr_x && ocean[curr_y][curr_x - 1].alive <= target) {
					updateCell(&ocean[curr_y][curr_x], &ocean[curr_y][curr_x - 1]);
					return;
				}
			}

		}
		++y;

		++radius;
	}

	moveToTheNearestTarget(ocean, curr_x, curr_y, hunter, hunter);
}