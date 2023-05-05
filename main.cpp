#define NOMINMAX
#include "Constants.h"
#include <Windows.h>
#include <stdlib.h>
#include <Windows.h>
#include <strsafe.h>
#include "Environment.hpp"
#include <sstream>

using namespace sf;

Sprite plankton;
Sprite fish;
Sprite fish1;
Sprite shark;

OceanCell ocean[Y_SIZE][X_SIZE];
void fillOcean(OceanCell ocean[Y_SIZE][X_SIZE], Sprite plankton, Sprite fish, Sprite fish1, Sprite shark);
void checkFishStatus(OceanCell* cell);
void spawnAnimal(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y);
void randomMovement(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int walker);
void moveToTheNearestTarget(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int hunter, int target);

void printOcean(RenderWindow* window, float time) {
    
    for (int y = 0; y < Y_SIZE; ++y) {
        for (int x = 0; x < X_SIZE; ++x) {
            if (ocean[y][x].type == EMPTY) continue;
            Vector2f position;
            position = ocean[y][x].sprite.getPosition();
            position.x = (x * WINDOW_SIZE_X / X_SIZE - position.x) * time;
            position.y = (y * WINDOW_SIZE_Y / Y_SIZE - position.y) * time;
            ocean[y][x].sprite.move(position);
            ocean[y][x].isChecked = 0;
            window->draw(ocean[y][x].sprite);
        }
    }
}

void updateOcean() {
    for (int i = 0; i < Y_SIZE; ++i) {
        for (int j = 0; j < X_SIZE; ++j) {
            if (ocean[i][j].isChecked || ocean[i][j].type == EMPTY) continue;

            checkFishStatus(&ocean[i][j]);

            if (ocean[i][j].type == PLANKTON) {
                spawnAnimal(ocean, j, i);
                randomMovement(ocean, j, i, PLANKTON);
                ocean[i][j].isChecked = 1;
            }

            if (ocean[i][j].type == SHARK) {
                ++ocean[i][j].essense.lifeTime;
                if (ocean[i][j].essense.gaveBirth == 0) {
                    spawnAnimal(ocean, j, i);
                }
                moveToTheNearestTarget(ocean, j, i, SHARK, FISH);
            }

            if (ocean[i][j].type == FISH) {
                ++ocean[i][j].essense.lifeTime;
                if (ocean[i][j].essense.gaveBirth == 0) {
                    spawnAnimal(ocean, j, i);
                }
                moveToTheNearestTarget(ocean, j, i, FISH, PLANKTON);
            }
        }
    }
}

int main()
{
    RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Aquarium");

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("images/background.png");
    Sprite background;
    background.setTexture(backgroundTexture);

    Font font;
    font.loadFromFile("font/CyrilicOld.TTF");
    Text text("", font, 40);
    text.setFillColor(Color::Blue);
    text.setStyle(Text::Bold);
    int countDays = 0;

    Clock clock;
    Clock gameTimeClock;
    int gameSeconds = 0;

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
    shark.scale(Vector2f(-SHARK_SPRITE_SCALE, SHARK_SPRITE_SCALE));

    fillOcean(ocean, plankton, fish, fish1, shark);

    while (window.isOpen())
    {
        float fps = clock.getElapsedTime().asSeconds();
        gameSeconds = gameTimeClock.getElapsedTime().asSeconds();
        int printSeconds = gameSeconds % 60;
        int printMinutes = gameSeconds / 60;
        int printHours = gameSeconds / 3600;
        clock.restart();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);

        printOcean(&window, fps);
        updateOcean();

        std::ostringstream gameTimeString;
        gameTimeString << printHours <<"h" << ":" << printMinutes << "m" << ":" << printSeconds << "s";
        text.setString("Time: " + gameTimeString.str());
        text.setPosition(WINDOW_SIZE_X - 310, 5);
        window.draw(text);

        /*std::ostringstream daysTimeString;
        daysTimeString << countDays++ / (gameSeconds + 1);
        text.setString("FPS: " + daysTimeString.str());
        text.setPosition(WINDOW_SIZE_X - 310, 50);
        window.draw(text);*/

        window.display();
        //Sleep(40);
        
    }

    return 0;
}