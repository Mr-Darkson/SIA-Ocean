#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include < time.h >
#include "Constants.h"
#include "Environment.h"

void printOcean(OceanCell [Y_SIZE][X_SIZE]);
<<<<<<< HEAD
void fillZero(OceanCell [Y_SIZE][X_SIZE]);
void generatePlancton(OceanCell[Y_SIZE][X_SIZE]);
void generateFish(OceanCell[Y_SIZE][X_SIZE]);


int main() {
	OceanCell ocean[Y_SIZE][X_SIZE];
	fillZero(ocean);
	generatePlancton(ocean);
	generateFish(ocean);
	printOcean(ocean);
	//generateShark(ocean);

	for (int day = 1; ; ) {

=======
void fillOcean(OceanCell [Y_SIZE][X_SIZE]);
void moveToTheNearestTarget(OceanCell[Y_SIZE][X_SIZE], int, int, char, int, int);
void setcur(int, int);
void setCursor(int);

int main() {
	OceanCell ocean[Y_SIZE][X_SIZE];
	fillOcean(ocean);
	setCursor(0);

	for (int day = 1; 1; ) {
		printOcean(ocean);
		for (int i = 0; i < Y_SIZE; ++i)
			for (int j = 0; j < X_SIZE; ++j)
				if (ocean[i][j].alive == SHARK) 
					moveToTheNearestTarget(ocean, j, i, SHARK_SYMB, SHARK, PLANKTON);
		setcur(0, 0);
		Sleep(500);
>>>>>>> main
	}
}
	