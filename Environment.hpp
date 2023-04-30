#ifndef ENVIRONMENT
#define ENVIRONMENT
#define NOMINMAX
#include "SFML/Graphics.hpp"

typedef struct {
    int gaveBirth;
    int hunger;
    int lifeTime;
} Essense;

typedef struct {
    int type;
    int isChecked;
    Essense essense;
    sf::Sprite sprite;
}OceanCell;

#endif 