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




int main() {
	OceanCell ocean[Y_SIZE][X_SIZE];
	fillZero(ocean);
	generatePlancton(ocean);
	printOcean(ocean);
	//generateFish(ocean);
	//generateShark(ocean);
	
	
	//for (int day = 0; 1; ) {
	//	
	//	//sleep(1);

	//}
	
}