#pragma once

#include "entity.h"

class Ghost : protected Entity {
private:

	std::vector<Vertex> data = {
		{{0.f, 0.f}, {1.f, 0.f, 0.f}},
		{{0.1f, 0.f}, {1.f, 0.f, 0.f}},
		{{0.f, -0.1f}, {1.f, 0.f, 0.f}},
		{{0.1f, -0.1f}, {1.f, 0.f, 0.f}}
	};

	GLuint indices[6] = { 0, 1, 2,
						1, 2, 3 };

	const GLfloat speed = 0.0055f;

	/*	Direction in which ghost will move.
	0	=	North	/	Up
	1	=	East	/	Right
	2	=	South	/	Down
	3	=	West	/	Left
	*/
	int direction = 0;

	//Float that decides where the ghost is supposed to move.
	GLfloat targetLocation;

public:
	//Creates ghost object with position, colors and all buffers
	Ghost();

	//Buffers data and draws ghost.
	void draw();

	//Find middle position of a ghost.
	void findMiddle();

	//Places ghost somewhere in playable area.
	void teleport(GLfloat centerX, GLfloat centerY);

	//Makes the ghost move depending on the direction integer.
	void move();

	//Decides which direction the ghost is going to move in. It's mainly used in Manager.
	void setDirection(int dir);

	//For manager, gets current direction.
	int getDirection();

	//Gets current middle position of a ghost.
	GLfloat* getMiddle();

	//Sets where the ghost is supposed to go.
	void setTargetLocation(GLfloat tar);

	//Get the supposed position the ghost is supposed to go
	GLfloat getTargetLocation();

	//Decide the size of the ghost.
	void setSize(GLfloat sizeX, GLfloat sizeY);
};
