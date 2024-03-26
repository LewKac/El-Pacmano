#ifndef __ENTITY_H
#define __ENTITY_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stb_image.h>
#include <vector>
#include "glutil.h"

class Entity {
protected:
	//Contains position, colors and texture
	struct Vertex
	{
		glm::vec2 position;
		glm::vec3 colors;
		glm::vec2 tex;
	};

	GLuint indices[6];

	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	GLuint tex;

	GLfloat middle[2];

	//Distance from middle to edge of entity.
	GLfloat x;
	GLfloat y;

public:
	Entity();

	virtual void buffer(GLuint& vao);
	virtual void draw(GLuint& vao);
};
#endif