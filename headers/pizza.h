#ifndef __PIZZA_H
#define __PIZZA_H

#include "../headers/entity.h"
#include "../headers/pacman.h"

class Pizza : public Entity {
private:
	GLuint indices[6] = { 0, 1, 2,
						  1, 2, 3 };

	std::vector<Vertex> data = {
		{{0.0f, 0.0f}, {1.f, 0.f, 0.f}},
		{{0.06f, 0.0f}, {1.f, 0.f, 0.f}},
		{{0.0f, -0.06f}, {1.f, 0.f, 0.f}},
		{{0.06f, -0.06f}, {1.f, 0.f, 0.f}}
	};

	GLfloat middle[2];
public:
	//Creates a pizza element.
	Pizza();

	//Draws pizza every frame.
	void draw();

	//Is called whenever a pizza is consumed by Pacman. Removes a pizza from the playground.
	void DIE();

	//Finds position of a pizza
	void findMiddle();

	GLfloat* getMiddle();
	//Move pizza to a specific position
	void teleport(GLfloat dotX, GLfloat dotY);

	//TODO: Useful or not?

	//Sets size of a pizza
	void setSize(GLfloat sizeX, GLfloat sizeY);
};

#endif
