#pragma once

#include "entity.h"

class Wall : public Entity {
private:
	std::vector<Vertex> data = {
	{{0.f, 0.f}, {0.1f, 0.1f, 0.45f}},
	{{0.f, 0.f}, {0.1f, 0.1f, 0.45f}},
	{{0.f, 0.f}, {0.1f, 0.1f, 0.45f}},
	{{0.f, 0.f}, {0.1f, 0.1f, 0.45f}}
	};

	GLuint indices[6] = { 0, 1, 2,
						  1, 2, 3 };

	GLfloat x = 0.19f;
	GLfloat y = 0.09f;

public:
	Wall();
	void initialize();
	void teleport(GLfloat x, GLfloat y);
	void draw();
	void setSize(GLfloat sizeX, GLfloat sizeY);
};
