#ifndef ENVIRONMENT
#define ENVIRONMENT

typedef struct Fish {
	int lifeTime;
} Fish;

typedef struct Plankton {
	int lifeTime;
}Plankton;

typedef struct OceanCell {
	int alive; //0 - null | 1 - plankton | 2 - fish | 3 - shark
	char symbol;
	Plankton* plankton;
	Fish* fish;
}OceanCell;


#endif 