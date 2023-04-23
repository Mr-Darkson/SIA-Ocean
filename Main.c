
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
void traxPlancton(OceanCell ocean[X_SIZE][Y_SIZE], int x, int y);
void diedPlankton(OceanCell ocean[X_SIZE][Y_SIZE], int x, int y);


int main() {
	OceanCell ocean[Y_SIZE][X_SIZE];
	fillZero(ocean);
	generatePlancton(ocean);
	printOcean(ocean);


	for (int day = 0; 1; day++) {
		
		for (int i = 0; i < Y_SIZE; i++) {
			for (int j = 0; j < X_SIZE; j++) {

				switch (ocean[i][j].alive)
				{
				case 0: //null
					break;

				case 1: //Plankton
					if (day % 1 == 0) {
						traxPlancton(ocean, i, j);
					}
					ocean[i][j].plankton.lifeTime--;
					if (ocean[i][j].plankton.lifeTime == 0) {
						diedPlankton(ocean, i, j);
					}
					break;
				case 2: //Fish

					break;
				case 3: //Plankton

					break;
				default:
					break;
				}
			}
		}
		printOcean(ocean);
		Sleep(3000);
	}
}
	