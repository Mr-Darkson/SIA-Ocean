#ifndef CONSTANTS
#define CONSTANTS


#define X_SIZE 10
#define Y_SIZE 10

#define EMPTY 0
#define SPACE ' '

#define PLANKTON 1
#define PLANKTON_SYMB '`'
#define PLANKTON_COUNT ((X_SIZE * Y_SIZE) / 100) * 10 //last number - %
#define PLANKTON_LIFETIME 5

#define FISH 2
#define FISH_SYMB '<'
#define FISH_COUNT ((X_SIZE * Y_SIZE) / 100) * 2 //last number - %
#define FISH_HUNGER 10
#define FISH_LIFETIME 30



#define SHARK 3
#define SHARK_SYMB '@'
#define SHARK_HUNGER 100
#define SHARK_LIFETIME 100
#define COUNT_SHARKS 20

#endif