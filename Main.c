#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include < time.h >
#include "Constants.h"
#include "Environment.h"

void printOcean(OceanCell [Y_SIZE][X_SIZE]);
void generatePlancton(OceanCell[Y_SIZE][X_SIZE]);
void generateFish(OceanCell[Y_SIZE][X_SIZE]);
void fillOcean(OceanCell [Y_SIZE][X_SIZE]);
void moveToTheNearestTarget(OceanCell[Y_SIZE][X_SIZE], int, int, int, int);
void setcur(int, int);
void setCursor(int);
void checkFishStatus(OceanCell*);

int main() {
	OceanCell ocean[Y_SIZE][X_SIZE];
	fillOcean(ocean);
	//setCursor(0);

	for (int day = 1; 1; ) {
		printOcean(ocean);
		for (int i = 0; i < Y_SIZE; ++i) {
			for (int j = 0; j < X_SIZE; ++j) {

				if (ocean[i][j].alive == PLANKTON) {
					++ocean[i][j].plankton.lifeTime;
					continue;
				}

				checkFishStatus(&ocean[i][j]);

				if (ocean[i][j].alive == SHARK) { //add fish
					moveToTheNearestTarget(ocean, j, i, SHARK, PLANKTON);
					++ocean[i][j].shark.lifeTime;
					continue;
				}

			}
		}
		setcur(0, 0);
		Sleep(500);
	}
}
	