#ifndef CONSTANTS
#define CONSTANTS


#define X_SIZE 100
#define Y_SIZE 50


#define EMPTY 0
#define SPACE ' '


#define PLANKTON 1
#define PLANKTON_SYMB '`'
#define PLANKTON_LIFETIME 10
#define PLANKTON_COUNT ((X_SIZE * Y_SIZE) / 100) * 30 //last number - %



#define FISH 2
#define FISH_SYMB '<'
#define FISH_COUNT ((X_SIZE * Y_SIZE) / 100) * 0.3 //last number - %
#define FISH_HUNGER 20
#define FISH_VISION_RADIUS 40
#define FISH_LIFETIME 70
#define FISH_BORN_HUNGER_LIMIT 11
#define MATURE_FISH_AGE 40
#define CHANCE_FISH_BORN_FIVE 20
#define CHANCE_FISH_BORN_THREE 22
#define CHANCE_FISH_BORN_ONE 28



#define SHARK 3
#define SHARK_SYMB '@'
#define SHARK_HUNGER 70
#define SHARK_BORN_HUNGER_LIMIT 20
#define SHARK_LIFETIME 120
#define SHARK_VISION_RADIUS 40
#define COUNT_SHARKS 7
#define MATURE_SHARK_AGE 70
#define CHANCE_SHARK_BORN_TWINS 20
#define CHANCE_SHARK_BORN_ONE 40

#endif