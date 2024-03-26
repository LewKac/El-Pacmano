#ifndef __PACMAN_H
#define __PACMAN_H

#include "../headers/entity.h"

class Pacman : public Entity {
private:
	GLuint indices[6] =
	{
		0, 1, 2,
		1, 2, 3
	};

	std::vector<Vertex> data =
	{
	{{0.0f, 0.0f},		{1.f, 1.f, 1.f},	{0.01f, 0.035f}},	//Vertex 1
	{{0.125f, 0.0f},	{1.f, 1.f, 1.f},	{0.17f, 0.035f}},	//Vertex 2
	{{0.0f, -0.125f},	{1.f, 1.f, 1.f},	{0.01f, 0.235f}},	//Vertex 3
	{{0.125f, -0.125f}, {1.f, 1.f, 1.f},	{0.17f, 0.235f}}	//Vertex 4
	};

	const float speed = 0.005f;
	bool check = false;

	GLfloat x = 0.19f;
	GLfloat y = 0.09f;

	//	-----	This is how it's supposed to be, but something goes went bad when used in CMake.
	//	-----	Current version uses static float spritePosition[2] in move function.
	//  Position in the spritesheet
	//	float spritePosition[2];

	int direction = 1;

public:
	//Creates a new Pacman object and assigns the position and color.
	Pacman();

	void DIE();

	//Load whole spritesheet of pacman.png
	void loadSprite();

	//Function used to draw Pacman every frame.
	void draw();

	//Whenever Pacman moves, this function is called to give Pacman new position.
	void move(GLuint shader);

	//Find middle point of Pacman
	void findMiddle();

	//Getter for middle position. Used by Manager
	GLfloat* getMiddle();

	//Sets how big Pacman should be.
	void setSize(GLfloat sizeX, GLfloat sizeY);

	//Teleports Pacman to a position. Takes center of where we want to spawn pacman as argument and function extends him automatically.
	void teleport(GLfloat dotX, GLfloat dotY);

	int getDirection();

	void setDirection(int directionArg);
};

#endif
