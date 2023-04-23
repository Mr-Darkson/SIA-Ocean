#ifndef CONSTANTS
#define CONSTANTS


#define X_SIZE 10
#define Y_SIZE 10

#define EMPTY 0
#define SPACE ' '

#define PLANKTON 1
#define PLANKTON_SYMB '`'
<<<<<<< HEAD
#define PLANKTON_COUNT ((X_SIZE * Y_SIZE) / 100) * 10 //last number - %
#define PLANKTON_LIFETIME 5
=======
#define PLANKTON_COUNT ((X_SIZE * Y_SIZE) / 100) * 15 //last number - %
>>>>>>> 5f3e45f594fe8ddda7ba43ea73724b9a7889344a

#define FISH 2
#define FISH_SYMB '<'
#define FISH_COUNT ((X_SIZE * Y_SIZE) / 100) * 2 //last number - %
#define FISH_HUNGER 10
#define FISH_LIFETIME 30
#define MATURE_FISH_AGE 10
#define CHANCE_FISH_BORN_FIVE 0.2
#define CHANCE_FISH_BORN_THREE 0.5
#define CHANCE_FISH_BORN_ONE 0.9



#define SHARK 3
#define SHARK_SYMB '@'
#define SHARK_HUNGER 30
#define SHARK_LIFETIME 100
#define COUNT_SHARKS 10
#define MATURE_SHARK_AGE 20
#define CHANCE_SHARK_BORN_TWINS 0.2
#define CHANCE_SHARK_BORN_ONE 0.8

#endif