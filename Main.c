
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include < time.h >
#include "Constants.h"
#include "Environment.h"


void printOcean(OceanCell [Y_SIZE][X_SIZE]);
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

	}
}
	