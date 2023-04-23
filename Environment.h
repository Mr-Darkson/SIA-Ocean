#ifndef ENVIRONMENT
#define ENVIRONMENT

typedef struct Fish {
	int gaveBirth;
	int hunger;
	int lifeTime;
} Fish;

typedef struct Plankton {
	int lifeTime;
}Plankton;

typedef struct Shark {
	int gaveBirth;
	int hunger;
	int lifeTime;
}Shark;

typedef struct OceanCell {
	int alive; //0 - null | 1 - plankton | 2 - fish | 3 - shark
	int isChecked;
	char symbol;
	Fish fish;
	Plankton plankton;
	Shark shark;
}OceanCell;

#endif 