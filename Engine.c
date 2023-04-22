#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Environment.h"

void fillZero(OceanCell ocean[Y_SIZE][X_SIZE]) {
	for (int y = 0; y < Y_SIZE; y++) {
		for (int x = 0; x < X_SIZE; x++) {
			ocean[y][x].symbol = VOID;
		}
	}
}

void printOcean(OceanCell ocean[Y_SIZE][X_SIZE]) {
	for (int y = 0; y < Y_SIZE; y++) {
		for (int x = 0; x < X_SIZE; x++) {
			printf("%c", ocean[y][x].symbol);
		}
		printf("\n");
	}