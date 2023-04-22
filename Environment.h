#ifndef ENVIRONMENT
#define ENVIRONMENT

typedef struct Plankton {
	int lifeTime;
}Plankton;

typedef struct OceanCell {
	int alive; //0 - null | 1 - plankton | 2 - fish | 3 - shark
	char symbol;
	Plankton* plankton;
}OceanCell;


#endif 
