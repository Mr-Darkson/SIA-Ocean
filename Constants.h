#ifndef CONSTANTS
#define CONSTANTS


#define X_SIZE 100
#define Y_SIZE 40

#define FISH_COUNT ((X_SIZE * Y_SIZE) / 100) * 4 //last number - %
#define PLANKTON_COUNT ((X_SIZE * Y_SIZE) / 100) * 6 //last number - %
#define COUNT_SHARKS 1

#define EMPTY 0
#define PLANKTON 1
#define FISH 2
#define SHARK 3

#define PLANKTON_SYMB '`'
#define FISH_SYMB '<'
#define SHARK_SYMB '@'

#define SHARK_HUNGER 20
<<<<<<< HEAD
#define SHARK_LIFETIME 1
=======
#define SHARK_LIFETIME 1000
#define COUNT_SHARKS 10
>>>>>>> d7bd694d1f6737d1bdcf194c03a5535565118e34

#define SPACE ' '
#endif