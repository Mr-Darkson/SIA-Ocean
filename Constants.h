#ifndef CONSTANTS
#define CONSTANTS


#define X_SIZE 180
#define Y_SIZE 60

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
#define FISH_VISION_RADIUS 30
#define FISH_LIFETIME 20
#define FISH_BORN_HUNGER_LIMIT 4
#define MATURE_FISH_AGE 10
#define CHANCE_FISH_BORN_FIVE 20
#define CHANCE_FISH_BORN_THREE 30
#define CHANCE_FISH_BORN_ONE 65



#define SHARK 3
#define SHARK_SYMB '@'
#define SHARK_HUNGER 30
#define SHARK_BORN_HUNGER_LIMIT 10
#define SHARK_LIFETIME 30
#define SHARK_VISION_RADIUS 40
#define COUNT_SHARKS 15
#define MATURE_SHARK_AGE 20
#define CHANCE_SHARK_BORN_TWINS 45
#define CHANCE_SHARK_BORN_ONE 55

#endif