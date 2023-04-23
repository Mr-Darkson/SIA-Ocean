#ifndef CONSTANTS
#define CONSTANTS


#define X_SIZE 100
#define Y_SIZE 40

#define EMPTY 0
#define SPACE ' '

#define PLANKTON 1
#define PLANKTON_SYMB '`'
#define PLANKTON_LIFETIME 15

#define PLANKTON_COUNT ((X_SIZE * Y_SIZE) / 100) * 50 //last number - %


#define FISH 2
#define FISH_SYMB '<'
#define FISH_COUNT ((X_SIZE * Y_SIZE) / 100) * 2 //last number - %
#define FISH_HUNGER 10
#define FISH_LIFETIME 30
#define MATURE_FISH_AGE 10
#define CHANCE_FISH_BORN_FIVE 15
#define CHANCE_FISH_BORN_THREE 35
#define CHANCE_FISH_BORN_ONE 65



#define SHARK 3
#define SHARK_SYMB '@'
#define SHARK_HUNGER 30
#define SHARK_LIFETIME 100
#define COUNT_SHARKS 1
#define MATURE_SHARK_AGE 20
#define CHANCE_SHARK_BORN_TWINS 100
#define CHANCE_SHARK_BORN_ONE 50

#endif