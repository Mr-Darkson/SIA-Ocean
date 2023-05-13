#define NOMINMAX
#include "Constants.h"
#include <Windows.h>
#include <stdlib.h>
#include <Windows.h>
#include <strsafe.h>
#include "Environment.hpp"
#include <sstream>
#include <math.h>
#include<cstdio>
#include<ctime>

using namespace sf;

Sprite plankton;
Sprite fish;
Sprite fish1;
Sprite shark;
Clock gameTimeClock;
Text gameTime;
int gameSeconds = 0;

OceanCell ocean[Y_SIZE][X_SIZE];
void fillOcean(OceanCell ocean[Y_SIZE][X_SIZE], Sprite plankton, Sprite fish, Sprite fish1, Sprite shark);
void checkFishStatus(OceanCell* cell);
void spawnAnimal(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y);
void moveToTheNearestTarget(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int hunter, int target);
void randomMovement(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y);
void invertScale(OceanCell* cell);

void frameDelay(float delay) {
    Clock time;
    while (time.getElapsedTime().asSeconds() < delay);
}

void timePrint(RenderWindow *window) {
    gameSeconds = gameTimeClock.getElapsedTime().asSeconds();
    int printSeconds = gameSeconds % 60;
    int printMinutes = gameSeconds / 60;
    int printHours = gameSeconds / 3600;

    std::ostringstream gameTimeString;
    gameTimeString << printHours << "h" << ":" << printMinutes << "m" << ":" << printSeconds << "s";
    gameTime.setString("Time: " + gameTimeString.str());
    gameTime.setPosition(WINDOW_SIZE_X - 310, 5);
    window->draw(gameTime);
}

void printOcean(RenderWindow* window, Sprite background) {
    for (int k = 0; k < WINDOW_SIZE_X / X_SIZE; k++) {

        for (int y = 0; y < Y_SIZE; ++y) {
            for (int x = 0; x < X_SIZE; ++x) {
                if (ocean[y][x].type == EMPTY) continue;
                Vector2f position = ocean[y][x].sprite.getPosition();
                float diffX = (x * WINDOW_SIZE_X / X_SIZE) - position.x;
                float diffY = (y * WINDOW_SIZE_Y / Y_SIZE) - position.y;
                if (ocean[y][x].type == SHARK) {
                    position.x = (diffX > 0 ? 2 : -2);
                    position.y = (diffY > 0 ? 2 : -2) * ((WINDOW_SIZE_Y / Y_SIZE) / (WINDOW_SIZE_X / X_SIZE));
                }
                else {
                    position.x = (diffX > 0 ? 1 : -1);
                    position.y = (diffY > 0 ? 1 : -1) * ((WINDOW_SIZE_Y / Y_SIZE) / (WINDOW_SIZE_X / X_SIZE));
                }
                
                
                ocean[y][x].sprite.move(position);
                ocean[y][x].isChecked = 0;
            }
        }

        window->draw(background);
        for (int y = 0; y < Y_SIZE; ++y) {
            for (int x = 0; x < X_SIZE; ++x) {
                if (ocean[y][x].type == EMPTY) continue;
                window->draw(ocean[y][x].sprite);
            }
        }

        timePrint(window);
        frameDelay(0.009);
        window->display();
    }
}

void updateOcean() {
    for (int i = 0; i < Y_SIZE; ++i) {
        for (int j = 0; j < X_SIZE; ++j) {
            if (ocean[i][j].isChecked || ocean[i][j].type == EMPTY) continue;

            checkFishStatus(&ocean[i][j]);
            ++ocean[i][j].essense.lifeTime;

            if (ocean[i][j].essense.gaveBirth == 0) {
                spawnAnimal(ocean, j, i);
            }

            if (ocean[i][j].type == PLANKTON) {
                randomMovement(ocean, j, i);
                ocean[i][j].isChecked = 1;
            }

            if (ocean[i][j].type == SHARK) {
                moveToTheNearestTarget(ocean, j, i, SHARK, FISH);
            }

            if (ocean[i][j].type == FISH) {
                moveToTheNearestTarget(ocean, j, i, FISH, PLANKTON);
            }
        }
    }
}

int main() {
    RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Aquarium");

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("images/background.png");
    Sprite background;
    background.setTexture(backgroundTexture);

    Font font;
    font.loadFromFile("font/CyrilicOld.TTF");
    gameTime.setFont(font);
    gameTime.setStyle(Text::Bold);
    gameTime.setFillColor(Color::Blue);
    gameTime.setCharacterSize(40);

    Texture planktonTexture;
    planktonTexture.loadFromFile("images/plankton.png");
    plankton.setTexture(planktonTexture);
    plankton.scale(Vector2f(PLANKTON_SPRITE_SCALE, PLANKTON_SPRITE_SCALE));

    Texture fishTexture;
    fishTexture.loadFromFile("images/fish.png");
    fish.setTexture(fishTexture);
    fish.scale(Vector2f(FISH_SPRITE_SCALE, FISH_SPRITE_SCALE));

    Texture fish1Texture;
    fish1Texture.loadFromFile("images/fish2.png");
    fish1.setTexture(fish1Texture);
    fish1.scale(Vector2f(FISH1_SPRITE_SCALE, FISH1_SPRITE_SCALE));

    Texture sharkTexture;
    sharkTexture.loadFromFile("images/shark.png");
    shark.setTexture(sharkTexture);
    shark.scale(Vector2f(SHARK_SPRITE_SCALE, SHARK_SPRITE_SCALE));

    fillOcean(ocean, plankton, fish, fish1, shark);

    while (window.isOpen()) {
       
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);

        updateOcean();
        printOcean(&window, background);
    }

    return 0;
}
