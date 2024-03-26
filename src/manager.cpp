#include "glutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "../headers/pacman.h"
#include "../headers/pizza.h"
#include "../headers/wall.h"
#include "../headers/ghost.h"
#include "../headers/manager.h"

/*Used to create an abstract map of level
w = wall, p = pizza, P = pacman, g = ghost */
GLfloat spawnPosition[2];

//The abstract map - id est the level - itself
tile mapAbstract[SIZE_Y][SIZE_X] = {
  w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w,
w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w,
w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w,
w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w,
w, g, p, p, p, p, p, p, p, p, p, p, p, w, w, p, p, p, p, p, p, p, p, p, p, p, p, w,
w, p, w, w, w, w, p, w, w, w, w, w, p, w, w, p, w, w, w, w, w, p, w, w, w, w, p, w,
w, p, w, w, w, w, p, w, w, w, w, w, p, w, w, p, w, w, w, w, w, p, w, w, w, w, p, w,
w, p, w, w, w, w, p, w, w, w, w, w, p, w, w, p, w, w, w, w, w, p, w, w, w, w, p, w,
w, p, p, p, p, g, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, w,
w, p, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, p, w,
w, p, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, p, w,
w, p, p, p, p, p, p, w, w, p, p, p, p, w, w, p, p, p, p, w, w, p, p, p, p, p, p, w,
w, w, w, w, w, w, p, w, w, w, w, w, p, w, w, p, w, w, w, w, w, p, w, w, w, w, w, w,
w, w, w, w, w, w, p, w, w, w, w, w, p, w, w, p, w, w, w, w, w, p, w, w, w, w, w, w,
w, w, w, w, w, w, p, w, w, p, p, p, p, p, p, p, p, p, p, w, w, p, w, w, w, w, w, w,
w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w,
w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w,
P, p, p, p, p, p, p, p, p, p, w, w, w, w, w, w, w, w, p, p, p, p, p, p, p, p, p, p,
w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w,
w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w,
w, w, w, w, w, w, p, w, w, p, p, p, p, p, p, p, p, p, p, w, w, p, w, w, w, w, w, w,
w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w,
w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w,
w, p, p, p, p, p, p, p, p, p, p, p, p, w, w, p, p, p, p, p, p, p, p, p, p, p, p, w,
w, p, w, w, w, w, p, w, w, w, w, w, p, w, w, p, w, w, w, w, w, p, w, w, w, w, p, w,
w, p, w, w, w, w, p, w, w, w, w, w, p, w, w, p, w, w, w, w, w, p, w, w, w, w, p, w,
w, p, p, p, w, w, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, w, w, p, p, p, w,
w, w, w, p, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, p, w, w, w,
w, w, w, p, w, w, p, w, w, p, w, w, w, w, w, w, w, w, p, w, w, p, w, w, p, w, w, w,
w, p, p, p, p, p, p, w, w, p, p, p, p, w, w, p, p, p, p, w, w, p, p, p, p, p, p, w,
w, p, w, w, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, w, w, p, w,
w, p, w, w, w, w, w, w, w, w, w, w, p, w, w, p, w, w, w, w, w, w, w, w, w, w, p, w,
w, g, p, p, p, p, p, g, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, p, w,
w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w,
w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w,
w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w
};

//Used to convert OpenGL coordinates to tilemap
GLfloat* findTile(GLfloat x, GLfloat y) {
	//Variables used to iterate throught the whole OpenGL coordinate system
	GLfloat current_x_left = -1.f;
	GLfloat current_y_upper = 1.f;

	//The variable that will be returned, stores two integers that represent position on the tilemap
	GLfloat* location = new GLfloat[2];

	int j = 0; int i = 0;
	location[0] = i; location[1] = j;

	//Starting with -1 because map tiles start with 0
	//It just works
	for (i = -1; i < SIZE_Y; i++) {
		//Goes through rows (hence y coordinate)
		if (current_y_upper > y) {
			current_y_upper -= ONE_Y;
			continue;
		}

		//Goes through columns (hence x coordinate)
		for (int j = -1; j < SIZE_X; j++) {
			if (current_x_left < x) {
				current_x_left += ONE_X;
				continue;
			}

			//Returns position
			location[0] = i; location[1] = j;
			return location;
		}
	}

	//Should never fire
	//If it fired, then the passed arguments are beyond [-1; 1]
	location[0] = -1; location[1] = -1;
	return location;
}

//Checks wheteher a coordinate is a wall
bool isWall(GLfloat x, GLfloat y) {
	GLfloat* check = findTile(x, y);

	if (mapAbstract[int(check[0])][int(check[1])] == 0) {
		delete[] check;
		return true;
	}
	delete[] check;
	return false;
}

//One of the most important functions
//Searches throught abstract map and spawns entities accordingly
void spawn(std::vector<Wall*>& wallsArg, std::vector<Pizza*>& pizzasArg, std::vector<Ghost*>& ghostsArg, Pacman& pac) {
	//Goes through rows (hence y coordinate)
	for (int y = -1; y < SIZE_Y; y++) {
		//Goes through columns (hence x coordinate)
		for (int x = -1; x < SIZE_X; x++) {
			//If tile is a wall - spawn a wall
			if (mapAbstract[y][x] == w) {
				if (x == -1 || y == -1) {
					continue;
				}

				GLfloat counter_x = -1.f + (ONE_X * x);
				GLfloat counter_y = 1.f - (ONE_Y * y);

				Wall* tempWall = new Wall;
				//Set size relative to size of whole map and teleport
				tempWall->setSize(ONE_X / 2.f, ONE_Y / 2.f);
				tempWall->teleport(counter_x - (ONE_X / 2.f), counter_y - (ONE_Y / 2.f));
				wallsArg.push_back(tempWall);
			}

			//If tile is a pizza - spawn a pizza
			if (mapAbstract[y][x] == p) {
				if (x == -1 || y == -1) {
					continue;
				}

				GLfloat counter_x = -1.f + (ONE_X * x);
				GLfloat counter_y = 1.f - (ONE_Y * y);

				Pizza* tempPizza = new Pizza;
				//Set size relative to size of whole map and teleport
				tempPizza->setSize(ONE_X / 8.f, ONE_Y / 8.f);
				tempPizza->teleport(counter_x + (ONE_X / 4.f), counter_y - (ONE_Y / 2.f));
				pizzasArg.push_back(tempPizza);
			}

			//If tile is pacman - spawn pacman
			if (mapAbstract[y][x] == P) {
				if (x == -1 || y == -1) {
					continue;
				}

				GLfloat counter_x = -1.f + (ONE_X * x);
				GLfloat counter_y = 1.f - (ONE_Y * y);

				//Set size relative to size of whole map and teleport
				pac.setSize(ONE_X / 2, ONE_Y / 2);
				pac.teleport(counter_x + (ONE_X / 8.f), counter_y - (ONE_Y / 2.f));
				//Also save his position for reuse after death
				spawnPosition[0] = counter_x + (ONE_X / 8.f); spawnPosition[1] = counter_y - (ONE_Y / 2.f);
			}

			//If tile is a ghost - spawn a ghost
			if (mapAbstract[y][x] == g) {
				if (x == -1 || y == -1) {
					continue;
				}

				Ghost* tempGhost = new Ghost;

				GLfloat counter_x = -1.f + (ONE_X * x);
				GLfloat counter_y = 1.f - (ONE_Y * y);

				//Set size relative to size of whole map and teleport
				tempGhost->setSize(ONE_X / 4.f, ONE_Y / 4.f);
				tempGhost->teleport(counter_x + (ONE_X / 8.f), counter_y - ONE_Y / 2.f);
				ghostsArg.push_back(tempGhost);
			}
		}
	}
}

//Controls how a ghost moves
void moveGhost(Ghost* ghost) {
	//Random generator device for AI
	std::random_device seed{};
	std::mt19937 generator(seed());
	std::uniform_int_distribution<int> rng(0, 3);

	bool directions[4] = { false, false, false, false };
	int chosenDirection; int vacantDirections = 0;

	GLfloat* ghostMiddle = ghost->getMiddle();

	GLfloat* check = findTile(ghostMiddle[0], ghostMiddle[1]);

	int previousDirection = ghost->getDirection();

	//Checking whether the ghost has reached next tile in his previously chosen direction
	switch (previousDirection) {
		//North
	case 0:

		if (ghostMiddle[1] < ghost->getTargetLocation()) {
			delete[] check;
			return;
		}
		break;

		//East
	case 1:

		if (ghostMiddle[0] < ghost->getTargetLocation()) {
			delete[] check;
			return;
		}
		break;

		//South
	case 2:

		if (ghostMiddle[1] > ghost->getTargetLocation()) {
			delete[] check;
			return;
		}

		break;
		//West
	case 3:

		if (ghostMiddle[0] > ghost->getTargetLocation()) {
			delete[] check;
			return;
		}
		break;
	}

	//If the previous did not return - it means the ghost has reached next tile and needs a new direction

	//Checking which tiles around are not walls
	//North
	if (mapAbstract[int(check[0] + 1)][int(check[1])] != w) {
		directions[2] = true;
		vacantDirections++;
	}
	//East
	if (mapAbstract[int(check[0])][int(check[1]) + 1] != w) {
		directions[1] = true;
		vacantDirections++;
	}
	//South
	if (mapAbstract[int(check[0]) - 1][int(check[1])] != w) {
		directions[0] = true;
		vacantDirections++;
	}
	//West
	if (mapAbstract[int(check[0])][int(check[1]) - 1] != w) {
		directions[3] = true;
		vacantDirections++;
	}

	//If more than two tiles around are not wall or he's in a dead end
	if (vacantDirections >= 2 || vacantDirections == 1) {
		//Randomly choose a direction, that is not opposite of previous direction, except for dead ends
		do {
			chosenDirection = rng(generator);
		} while (!(directions[chosenDirection]) || ((((chosenDirection + 2) % 4) == previousDirection) && vacantDirections != 1));

		ghost->setDirection(chosenDirection);

		//Set target location to middle of next chosen tile
		//North
		switch (chosenDirection) {
		case 0: {
			GLfloat targetY = 1.f - float(check[0] - 1) * ONE_Y - ONE_Y / 2.f;
			ghost->setTargetLocation(targetY);
			break;
		}

			  //East
		case 1: {
			GLfloat targetY = -1.f + float(check[1] + 1) * ONE_X + ONE_X / 2.f;
			ghost->setTargetLocation(targetY);
			break;
		}

			  //South
		case 2: {
			GLfloat targetY = 1.f - float(check[0] + 1) * ONE_Y - ONE_Y / 2.f;
			ghost->setTargetLocation(targetY);
			break;
		}

			  //West
		case 3: {
			GLfloat targetY = -1.f + float(check[1] - 1) * ONE_X + ONE_X / 2.f;
			ghost->setTargetLocation(targetY);
			break;
		}
		}
	}

	delete[] check;
}

//Checks whether next tile in chosen direction is a wall or not
bool checkPac(Pacman& pac, int direction) {
	GLfloat* check = findTile(pac.getMiddle()[0], pac.getMiddle()[1]);

	switch (direction) {
	case 0:
		if (!(mapAbstract[int(check[0] - 1)][int(check[1])] == w)) {
			delete[] check;
			return false;
		}
		break;

	case 1:
		if (!(mapAbstract[int(check[0])][int(check[1] + 1)] == w)) {
			delete[] check;
			return false;
		}
		break;

	case 2:
		if (!(mapAbstract[int(check[0] + 1)][int(check[1])] == w)) {
			delete[] check;
			return false;
		}
		break;

	case 3:
		if (!(mapAbstract[int(check[0])][int(check[1] - 1)] == w)) {
			delete[] check;
			return false;
		}
		break;
	}

	return true;
	delete[] check;
}

//Checks whether pacman is standing on a pizza and eats it if he does
bool eatPizza(Pacman& pac, Pizza& pi) {
	GLfloat* checkPacman = findTile(pac.getMiddle()[0], pac.getMiddle()[1]);
	GLfloat* checkPizza = findTile(pi.getMiddle()[0], pi.getMiddle()[1]);

	if ((checkPacman[0] == checkPizza[0]) && (checkPacman[1] == checkPizza[1])) {
		delete[] checkPacman;
		delete[] checkPizza;
		return true;
	}
	delete[] checkPacman;
	delete[] checkPizza;
	return false;
}

//Checks whether pacman is standing on the same tile as a ghost and busts him if he does
bool pacmanBusted(Pacman& pac, Ghost& gho) {
	GLfloat* checkPacman = findTile(pac.getMiddle()[0], pac.getMiddle()[1]);
	GLfloat* checkGhost = findTile(gho.getMiddle()[0], gho.getMiddle()[1]);

	if ((checkPacman[0] == checkGhost[0]) && (checkPacman[1] == checkGhost[1])) {
		delete[] checkPacman;
		delete[] checkGhost;
		return true;
	}
	delete[] checkPacman;
	delete[] checkGhost;
	return false;
}