#ifndef ENVIRONMENT
#define ENVIRONMENT

typedef struct Plankton {
	int lifeTime;
}Plankton;

typedef struct Shark {
	int hunger;
	int lifeTime;
}Shark;

typedef struct OceanCell {
	int alive; //0 - null | 1 - plankton | 2 - fish | 3 - shark
	int isChecked;
	char symbol;
	Plankton plankton;
	Shark shark;
}OceanCell;

#endif 