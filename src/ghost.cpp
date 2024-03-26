#include "../headers/ghost.h"
#include <random>

Ghost::Ghost()
{
	//Create Vertex Array Objects
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Buffers to read position
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vector_byte_size(data), data.data(), GL_DYNAMIC_DRAW);

	//Buffers to read indices for positions
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6, indices, GL_DYNAMIC_DRAW);

	//Enable Vao
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, colors)));

	//For calculating the distance from middle to the edge of a ghost.
	x = abs(((data.data()[0].position[0] - data.data()[0].position[0]) + (data.data()[1].position[0] - data.data()[0].position[0])) / 2.f);
	y = abs(((data.data()[0].position[1] - data.data()[0].position[1]) + (data.data()[2].position[1] - data.data()[0].position[1])) / 2.f);

	findMiddle();

	setTargetLocation(middle[0]);

	//Unbind buffers.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Ghost::draw()
{
	//Enable correct buffers and vao
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vector_byte_size(data), data.data(), GL_DYNAMIC_DRAW);

	//Draw a ghost
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	//Disable buffers and vao
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Ghost::findMiddle()
{
	middle[0] = (data.data()[0].position[0] + data.data()[1].position[0]) / 2.f;
	middle[1] = (data.data()[0].position[1] + data.data()[2].position[1]) / 2.f;
}

GLfloat* Ghost::getMiddle() {
	return &middle[0];
}

void Ghost::teleport(GLfloat centerX, GLfloat centerY)
{
	data.data()[0].position[0] = centerX + x;
	data.data()[0].position[1] = centerY + y;

	data.data()[1].position[0] = data.data()[0].position[0] + 2 * x;
	data.data()[1].position[1] = data.data()[0].position[1];

	data.data()[2].position[0] = data.data()[0].position[0];
	data.data()[2].position[1] = data.data()[0].position[1] - 2 * y;

	data.data()[3].position[0] = data.data()[0].position[0] + 2 * x;
	data.data()[3].position[1] = data.data()[0].position[1] - 2 * y;

	findMiddle();

	setTargetLocation(middle[0]);
}

void Ghost::move()
{
	//0 = North ----- 1 = East ---- 2 = South ---- 3 = West
	if (direction == 0) {
		for (int i = 0; i < 4; i++) {
			data.data()[i].position[1] += speed;
		}
	}
	if (direction == 1) {
		for (int i = 0; i < 4; i++) {
			data.data()[i].position[0] += speed;
		}
	}
	if (direction == 2) {
		for (int i = 0; i < 4; i++) {
			data.data()[i].position[1] -= speed;
		}
	}
	if (direction == 3) {
		for (int i = 0; i < 4; i++) {
			data.data()[i].position[0] -= speed;
		}
	}

	findMiddle();
}

void Ghost::setSize(GLfloat sizeX, GLfloat sizeY) {
	x = sizeX;
	y = sizeY;
}

void Ghost::setDirection(int dir) {
	direction = dir;
}

int Ghost::getDirection() {
	return direction;
}

void Ghost::setTargetLocation(GLfloat tar) {
	targetLocation = tar;
}

GLfloat Ghost::getTargetLocation() {
	return targetLocation;
}