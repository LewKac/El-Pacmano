#include "../headers/wall.h"

Wall::Wall()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vector_byte_size(data), nullptr, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, colors)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Wall::teleport(GLfloat centerX, GLfloat centerY)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	data.data()[0].position[0] = centerX + x;
	data.data()[0].position[1] = centerY + y;

	data.data()[1].position[0] = data.data()[0].position[0] + 2 * x;
	data.data()[1].position[1] = data.data()[0].position[1];

	data.data()[2].position[0] = data.data()[0].position[0];
	data.data()[2].position[1] = data.data()[0].position[1] - 2 * y;

	data.data()[3].position[0] = data.data()[0].position[0] + 2 * x;
	data.data()[3].position[1] = data.data()[0].position[1] - 2 * y;

	glBufferData(GL_ARRAY_BUFFER, vector_byte_size(data), data.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Wall::draw()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Wall::setSize(GLfloat sizeX, GLfloat sizeY)
{
	x = sizeX;
	y = sizeY;
}