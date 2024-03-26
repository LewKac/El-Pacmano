#include "../headers/pizza.h"

Pizza::Pizza() {
	//Creating Vertex Array Object for one pizza
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Generate array buffer for positions of pizza
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vector_byte_size(data), data.data(), GL_DYNAMIC_DRAW);

	//Generate array buffer for indices
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6, indices, GL_DYNAMIC_DRAW);

	//Appoint and enable vao
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, colors)));
}

//Draws pizza in the window
void Pizza::draw()
{
	findMiddle();
	//Enable correct buffers and vao
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vector_byte_size(data), data.data(), GL_DYNAMIC_DRAW);

	//Draw a pizza
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Pizza::DIE() {
	glBindVertexArray(vao);
	glDeleteBuffers(1, &vbo);
	glBindVertexArray(0);
}

void Pizza::findMiddle()
{
	middle[0] = (data.data()[0].position[0] + data.data()[1].position[0]) / 2.f;
	middle[1] = (data.data()[0].position[1] + data.data()[2].position[1]) / 2.f;
}

GLfloat* Pizza::getMiddle()
{
	return &middle[0];
}

void Pizza::teleport(GLfloat centerX, GLfloat centerY) {
	data.data()[0].position[0] = centerX + x;
	data.data()[0].position[1] = centerY + y;

	data.data()[1].position[0] = data.data()[0].position[0] + 2 * x;
	data.data()[1].position[1] = data.data()[0].position[1];

	data.data()[2].position[0] = data.data()[0].position[0];
	data.data()[2].position[1] = data.data()[0].position[1] - 2 * y;

	data.data()[3].position[0] = data.data()[0].position[0] + 2 * x;
	data.data()[3].position[1] = data.data()[0].position[1] - 2 * y;
}

void Pizza::setSize(GLfloat sizeX, GLfloat sizeY)
{
	x = sizeX;
	y = sizeY;
}