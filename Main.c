#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include < time.h >
#include "Constants.h"
#include "Environment.h"

void printOcean(OceanCell [Y_SIZE][X_SIZE]);
void generatePlancton(OceanCell[Y_SIZE][X_SIZE]);
void traxPlancton(OceanCell ocean[X_SIZE][Y_SIZE], int x, int y);
void diedPlankton(OceanCell ocean[X_SIZE][Y_SIZE], int x, int y);
void generateFish(OceanCell[Y_SIZE][X_SIZE]);
void fillOcean(OceanCell [Y_SIZE][X_SIZE]);
void moveToTheNearestTarget(OceanCell[Y_SIZE][X_SIZE], int, int, int, int);
void setcur(int, int);
void setCursor(int);
void checkFishStatus(OceanCell*);
void randomMovement(OceanCell[Y_SIZE][X_SIZE], int x, int y);

void updateOcean(OceanCell ocean[Y_SIZE][X_SIZE]) {
	for (int i = 0; i < Y_SIZE; ++i) {
		for (int j = 0; j < X_SIZE; ++j) {
			if (ocean[i][j].isChecked) continue;

			checkFishStatus(&ocean[i][j]);

			if (ocean[i][j].alive == PLANKTON) {
				++ocean[i][j].plankton.lifeTime;
				randomMovement(ocean, j, i);
				ocean[i][j].isChecked = 1;
				continue;
			}

			if (ocean[i][j].alive == SHARK) { 
				moveToTheNearestTarget(ocean, j, i, SHARK, FISH);
				++ocean[i][j].shark.lifeTime;
				continue;
			}

			if (ocean[i][j].alive == FISH) {
				moveToTheNearestTarget(ocean, j, i, FISH, PLANKTON);
				++ocean[i][j].fish.lifeTime;
				continue;
			}
		}
	}
}

int main() {
	OceanCell ocean[Y_SIZE][X_SIZE];
	fillOcean(ocean);
	//setCursor(0);

	for (int day = 1; 1; day++) {
		printOcean(ocean);
		updateOcean(ocean);
		setcur(0, 0);
		Sleep(500);
	}
}
	