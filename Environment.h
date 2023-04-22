#ifndef ENVIRONMENT
#define ENVIRONMENT

typedef struct Fish {
	int lifeTime;
} Fish;

typedef struct Plankton {
	int lifeTime;
}Plankton;

typedef struct Shark {
	int hunger;
}Shark;

typedef struct OceanCell {
	int alive; //0 - null | 1 - plankton | 2 - fish | 3 - shark
	char symbol;
<<<<<<< HEAD
	Plankton* plankton;
	Fish* fish;
=======
	Plankton plankton;
	Shark shark;
>>>>>>> main
}OceanCell;

#endif 