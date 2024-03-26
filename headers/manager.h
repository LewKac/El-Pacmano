#ifndef __MANAGER_H
#define __MANAGER_H

#include "../headers/ghost.h"

/*Used to create an abstract map of level
w = wall, p = pizza, P = pacman, g = ghost */
typedef enum { w, p, P, g} tile;

//Used to save position of initial pacman spawn
extern GLfloat spawnPosition[2];

//Size of the level, might be changed to add bigger levels
int const SIZE_X = 28;
int const SIZE_Y = 36;

//Calculated size of one tile of the level
GLfloat const ONE_X = 2.f / SIZE_X;
GLfloat const ONE_Y = 2.f / SIZE_Y;

//Used to convert OpenGL coordinates to tilemap
GLfloat* findTile(GLfloat x, GLfloat y);

//Checks wheteher a coordinate is a wall
bool isWall(GLfloat x, GLfloat y);

//One of the most important functions
//Searches throught abstract map and spawns entities accordingly
void spawn(std::vector<Wall*>& wallsArg, std::vector<Pizza*>& pizzasArg, std::vector<Ghost*>& ghostsArg, Pacman& pac);

//Controls how a ghost moves
void moveGhost(Ghost* ghost);

//Controls pacman so that he does not moves int a wall
bool checkPac(Pacman& pac, int direction);

//Checks whether pacman is standing on a pizza and eats it if he does
bool eatPizza(Pacman& pac, Pizza& pi);

//Checks whether pacman is standing on the same tile as a ghost and busts him if he does
bool pacmanBusted(Pacman& pac, Ghost& gho);

#endif
