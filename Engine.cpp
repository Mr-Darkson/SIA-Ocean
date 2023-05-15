#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Constants.h"
#include "Environment.hpp"

void generatePlancton(OceanCell[Y_SIZE][X_SIZE], sf::Sprite);
void generateSharks(OceanCell[Y_SIZE][X_SIZE], sf::Sprite);
void generateFish(OceanCell ocean[Y_SIZE][X_SIZE], sf::Sprite, sf::Sprite);

void invertScale(OceanCell* cell) {
	cell->sprite.setScale(-cell->sprite.getScale().x, cell->sprite.getScale().y);
}

void fillOcean(OceanCell ocean[Y_SIZE][X_SIZE], sf::Sprite plankton, sf::Sprite fish, sf::Sprite fish1, sf::Sprite shark) {
	for (int y = 0; y < Y_SIZE; y++) {
		for (int x = 0; x < X_SIZE; x++) {
			ocean[y][x].type = EMPTY;
			ocean[y][x].essense.gaveBirth = 0;
			ocean[y][x].essense.hunger = 0;
			ocean[y][x].essense.lifeTime = 0;
		}
	}
	generateFish(ocean, fish, fish1);
	generatePlancton(ocean, plankton);
	generateSharks(ocean, shark);
}

void updateCell(OceanCell* oldCell, OceanCell* newCell) {
	if (oldCell->type == PLANKTON) {
		newCell->type = PLANKTON;
	}

	if (oldCell->type == SHARK) {
		if (newCell->type >= FISH && oldCell->essense.hunger >= SHARK_HUNGER / 5) {
			oldCell->essense.hunger -= SHARK_HUNGER / 20;
		}
		else {
			++oldCell->essense.hunger;
		}
		newCell->type = SHARK;
	}

	if (oldCell->type == FISH) {
		if (newCell->type == PLANKTON || newCell->type == FISH) {
			oldCell->essense.hunger = 0;
		}
		else {
			++oldCell->essense.hunger;
		}
		newCell->type = FISH;
	}

	newCell->isChecked = 1;
	newCell->essense.lifeTime = oldCell->essense.lifeTime;
	newCell->essense.hunger = oldCell->essense.hunger;
	newCell->essense.gaveBirth = oldCell->essense.gaveBirth;
	newCell->sprite = oldCell->sprite;

	oldCell->type = EMPTY;
}

void checkFishStatus(OceanCell* cell) {
	if (cell->type == SHARK) {
		if (cell->essense.hunger > SHARK_HUNGER || cell->essense.lifeTime > SHARK_LIFETIME) {
			cell->type = EMPTY;
		}
	}

	if (cell->type == FISH) {
		if (cell->essense.hunger > FISH_HUNGER || cell->essense.lifeTime > FISH_LIFETIME) {
			cell->type = EMPTY;
		}
	}

	if (cell->type == PLANKTON) {
		if (cell->essense.lifeTime > PLANKTON_LIFETIME) {
			cell->type = EMPTY;
		}
	}
}

int makeMoveIfEmpty(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int targ_x, int targ_y, int target) {

	int next_y;
	int next_x;

	if (ocean[curr_y][curr_x].type == SHARK) {
		int y_diff = targ_y - curr_y;
		int x_diff = targ_x - curr_x;
		next_y = curr_y + (y_diff / (abs(y_diff) ? abs(y_diff) : 1)) * (abs(y_diff) >= 2 ? 2 : 1);
		next_x = curr_x + (x_diff / (abs(x_diff) ? abs(x_diff) : 1)) * (abs(x_diff) >= 2 ? 2 : 1);
	}
	else {
		int y_diff = targ_y - curr_y;
		int x_diff = targ_x - curr_x;
		next_y = curr_y + (y_diff / (abs(y_diff) ? abs(y_diff) : 1));
		next_x = curr_x + (x_diff / (abs(x_diff) ? abs(x_diff) : 1));
	}

	if (ocean[next_y][next_x].type <= target) {
		updateCell(&ocean[curr_y][curr_x], &ocean[next_y][next_x]);
		return 1;
	}

	return 0;
}

void randomMovement(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y) {
	int new_x = curr_x - 1 + rand() % 3;
	int new_y = curr_y - 1 + rand() % 3;
	if (new_x >= 0 && new_x < X_SIZE && new_y >= 0 && new_y < Y_SIZE) {
		if (ocean[new_y][new_x].type >= ocean[curr_y][curr_x].type) return;
		updateCell(&ocean[curr_y][curr_x], &ocean[new_y][new_x]);
	}
}

void addAnimalInOcean(OceanCell ocean[Y_SIZE][X_SIZE], int x, int y, int target, sf::Sprite animal) {
	ocean[y][x].type = target;
	ocean[y][x].essense.hunger = 0;
	ocean[y][x].essense.lifeTime = 0;
	ocean[y][x].essense.gaveBirth = 0;
	ocean[y][x].sprite = animal;
}

void spawnAnimal(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y) {

	if (ocean[curr_y][curr_x].type == PLANKTON) {
		int chance = rand() % 2;
		if (chance == 0) {
			return;
		}

		int new_x = curr_x - 1 + rand() % 3;
		int new_y = curr_y - 1 + rand() % 3;
		if (new_x >= 0 && new_x < X_SIZE && new_y >= 0 && new_y < Y_SIZE) {
			if (ocean[new_y][new_x].type >= ocean[curr_y][curr_x].type) return;
			addAnimalInOcean(ocean, new_x, new_y, PLANKTON, ocean[curr_y][curr_x].sprite);
			return;
		}
	}

	if (ocean[curr_y][curr_x].type == FISH) {
		if (ocean[curr_y][curr_x].essense.lifeTime < MATURE_FISH_AGE || ocean[curr_y][curr_x].essense.hunger >= FISH_BORN_HUNGER_LIMIT)
			return;
		int bornChance = rand() % 100;
		if (bornChance < CHANCE_FISH_BORN_FIVE) {
			ocean[curr_y][curr_x].essense.gaveBirth = 1;
			return;
		}

		if (CHANCE_FISH_BORN_FIVE <= bornChance && bornChance < CHANCE_FISH_BORN_THREE) {
			for (int i = 0; i < 5; ++i) {
				int new_x = curr_x - 1 + rand() % 3;
				int new_y = curr_y - 1 + rand() % 3;
				if (new_x >= 0 && new_x < X_SIZE && new_y >= 0 && new_y < Y_SIZE) {
					if (ocean[new_y][new_x].type >= ocean[curr_y][curr_x].type) continue;
					addAnimalInOcean(ocean, new_x, new_y, FISH, ocean[curr_y][curr_x].sprite);
					ocean[curr_y][curr_x].essense.gaveBirth = 1;
				}
			}
			return;
		}

		if (CHANCE_FISH_BORN_THREE <= bornChance && bornChance < CHANCE_FISH_BORN_ONE) {
			for (int i = 0; i < 3; ++i) {
				int new_x = curr_x - 1 + rand() % 3;
				int new_y = curr_y - 1 + rand() % 3;
				if (new_x >= 0 && new_x < X_SIZE && new_y >= 0 && new_y < Y_SIZE) {
					if (ocean[new_y][new_x].type >= ocean[curr_y][curr_x].type) continue;
					addAnimalInOcean(ocean, new_x, new_y, FISH, ocean[curr_y][curr_x].sprite);
					ocean[curr_y][curr_x].essense.gaveBirth = 1;
				}
			}
			return;
		}

		if (CHANCE_FISH_BORN_ONE <= bornChance) {
			int new_x = curr_x - 1 + rand() % 3;
			int new_y = curr_y - 1 + rand() % 3;
			if (new_x >= 0 && new_x < X_SIZE && new_y >= 0 && new_y < Y_SIZE) {
				if (ocean[new_y][new_x].type >= ocean[curr_y][curr_x].type) return;
				addAnimalInOcean(ocean, new_x, new_y, FISH, ocean[curr_y][curr_x].sprite);
				ocean[curr_y][curr_x].essense.gaveBirth = 1;
				return;
			}
		}
	}

	if (ocean[curr_y][curr_x].type == SHARK) {
		if (ocean[curr_y][curr_x].essense.lifeTime < MATURE_SHARK_AGE || ocean[curr_y][curr_x].essense.hunger >= SHARK_BORN_HUNGER_LIMIT)
			return;
		int bornChance = rand() % 100;
		if (bornChance < CHANCE_SHARK_BORN_TWINS) {
			ocean[curr_y][curr_x].essense.gaveBirth = 1;
			return;
		}

		if (CHANCE_SHARK_BORN_TWINS <= bornChance && bornChance < CHANCE_SHARK_BORN_ONE) {
			for (int i = 0; i < 2; ++i) {
				int new_x = curr_x - 1 + rand() % 3;
				int new_y = curr_y - 1 + rand() % 3;
				if (new_x >= 0 && new_x < X_SIZE && new_y >= 0 && new_y < Y_SIZE) {
					if (ocean[new_y][new_x].type >= ocean[curr_y][curr_x].type) continue;
					addAnimalInOcean(ocean, new_x, new_y, SHARK, ocean[curr_y][curr_x].sprite);
					ocean[curr_y][curr_x].essense.gaveBirth = 1;
				}
			}
			return;
		}

		if (CHANCE_SHARK_BORN_ONE <= bornChance) {
			int new_x = curr_x - 1 + rand() % 3;
			int new_y = curr_y - 1 + rand() % 3;
			if (new_x >= 0 && new_x < X_SIZE && new_y >= 0 && new_y < Y_SIZE) {
				if (ocean[new_y][new_x].type >= ocean[curr_y][curr_x].type) return;
				addAnimalInOcean(ocean, new_x, new_y, SHARK, ocean[curr_y][curr_x].sprite);
				ocean[curr_y][curr_x].essense.gaveBirth = 1;
				return;
			}
		}
	}
}

int runFromHunter(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int from_x, int from_y, int target) {
	int y_diff = from_y - curr_y;
	int x_diff = from_x - curr_x;
	int next_y = curr_y - (y_diff / (abs(y_diff) ? abs(y_diff) : 1));
	int next_x = curr_x - (x_diff / (abs(x_diff) ? abs(x_diff) : 1));


	if (next_x >= 0 && next_x < X_SIZE && next_y >= 0 && next_y < Y_SIZE) {
		if (ocean[next_y][next_x].type <= target) {
			updateCell(&ocean[curr_y][curr_x], &ocean[next_y][next_x]);
			return 1;
		}
	}

	return 0;
}

void moveToTheNearestTarget(OceanCell ocean[Y_SIZE][X_SIZE], int curr_x, int curr_y, int hunter, int target) {

	OceanCell entity = ocean[curr_y][curr_x];
	if (entity.type == SHARK) {
		if (entity.essense.hunger < (SHARK_HUNGER / 5)) {
			randomMovement(ocean, curr_x, curr_y);
			return;
		}
	}

	int radius = 1;
	int radius_limit = hunter == FISH ? FISH_VISION_RADIUS : SHARK_VISION_RADIUS;

	while ((curr_x + radius < X_SIZE || curr_y + radius < Y_SIZE || curr_y - radius >= 0 || curr_x - radius >= 0) && radius <= (radius_limit)) {
		for (int y = curr_y > radius ? curr_y - radius : 0; y <= curr_y + radius && y < Y_SIZE; y++) {
			for (int x = curr_x > radius ? curr_x - radius : 0; x <= curr_x + radius && x < X_SIZE; x++) {
				if (ocean[y][x].type > hunter) {
					if (runFromHunter(ocean, curr_x, curr_y, x, y, target)) {
						return;
					}
				}
			}
		}

		++radius;
	}

	radius = 1;

	while ((curr_x + radius < X_SIZE || curr_y + radius < Y_SIZE || curr_y - radius >= 0 || curr_x - radius >= 0) && radius <= radius_limit) {

		int havchic[500][2];
		int count_havchic = 0;

		for (int y = curr_y > radius ? curr_y - radius : 0; y <= curr_y + radius && y < Y_SIZE; y++) {
			for (int x = curr_x > radius ? curr_x - radius : 0; x <= curr_x + radius && x < X_SIZE; x++) {
				if (abs(y - curr_y) != radius && abs(curr_x - x) != radius) {
					x = curr_x + radius - 1;
				}
				else if (ocean[y][x].type > hunter) {
					if (runFromHunter(ocean, curr_x, curr_y, x, y, target)) {
						return;
					}
				}
				else if (ocean[y][x].type == target) {
					havchic[count_havchic][0] = x;
					havchic[count_havchic][1] = y;
					count_havchic++;
				}
			}
		}

		if (count_havchic > 0) {
			int rand_start = rand() % count_havchic;
			if (makeMoveIfEmpty(ocean, curr_x, curr_y, havchic[rand_start][0], havchic[rand_start][1], target)) {
				return;
			}
			for (int i = (rand_start + 1) % count_havchic; i != rand_start; i = (i + 1) % count_havchic) {
				if (makeMoveIfEmpty(ocean, curr_x, curr_y, havchic[i][0], havchic[i][1], target)) {
					return;
				}
			}
		}


		++radius;
	}

	randomMovement(ocean, curr_x, curr_y);
}
