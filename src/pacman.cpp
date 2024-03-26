#include "../headers/pacman.h"
#include <cmath>
#include <iostream>

Pacman::Pacman() {
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

	loadSprite();

	//Enable Vao
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, colors)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tex)));

	findMiddle();
}

void Pacman::loadSprite() {
	int tW, tH;

	auto image = stbi_load("assets/spritesheet/pacman.png", &tW, &tH, nullptr, STBI_rgb_alpha);

	//Binds texture to pacman
	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tW, tH, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	//We want it to clamp; not repeat nor mirror
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	stbi_image_free(image);
}

void Pacman::draw()
{
	findMiddle();

	//Bind the correct buffers
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Send new location
	glBufferData(GL_ARRAY_BUFFER, vector_byte_size(data), data.data(), GL_DYNAMIC_DRAW);

	//Draw Pacman
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Pacman::setDirection(int directionArg) {
	direction = directionArg;
}

void Pacman::move(GLuint shader)
{
	//How many frames must pass for animation to pass
	static int spriteWait;

	//Workaround for texture
	static float spritePosition[2];

	//Access uniform from shader
	int texturePosition = glGetUniformLocation(shader, "posTex");

	switch (direction) {
		//North
	case 0:

		for (int i = 0; i < 4; i++)
		{
			data.data()[i].position[1] += speed;
		}
		spritePosition[1] = 0.235f;
		break;

		//East
	case 1:

		for (int i = 0; i < 4; i++)
		{
			data.data()[i].position[0] += speed;
		}
		spritePosition[1] = 0.735f;
		break;

		//South
	case 2:

		for (int i = 0; i < 4; i++)
		{
			data.data()[i].position[1] -= speed;
		}
		spritePosition[1] = 0.005f;
		break;

		//West
	case 3:

		for (int i = 0; i < 4; i++)
		{
			data.data()[i].position[0] -= speed;
		}
		spritePosition[1] = 0.485f;
		break;
	}

	//Cheeky way to delay transition between sprites
	spriteWait++;
	if (spriteWait > 5)
	{
		//Animation loop
		if (spritePosition[0] < 0.4f)
		{
			spritePosition[0] += 0.16f;
		}
		//When he's done with his loop, start from beginning
		else
		{
			spritePosition[0] = 0.0f;
		}
		spriteWait = 0;
	}

	glUniform2fv(texturePosition, 1, &spritePosition[0]);
}

int Pacman::getDirection() {
	return direction;
}

void Pacman::findMiddle()
{
	middle[0] = (data.data()[0].position[0] + data.data()[1].position[0]) / 2.f;
	middle[1] = (data.data()[0].position[1] + data.data()[2].position[1]) / 2.f;
}

GLfloat* Pacman::getMiddle() {
	return &middle[0];
}

void Pacman::teleport(GLfloat centerX, GLfloat centerY)
{
	data.data()[0].position[0] = centerX + x;
	data.data()[0].position[1] = centerY + y;

	data.data()[1].position[0] = data.data()[0].position[0] + 2 * x;
	data.data()[1].position[1] = data.data()[0].position[1];

	data.data()[2].position[0] = data.data()[0].position[0];
	data.data()[2].position[1] = data.data()[0].position[1] - 2 * y;

	data.data()[3].position[0] = data.data()[0].position[0] + 2 * x;
	data.data()[3].position[1] = data.data()[0].position[1] - 2 * y;
}

void Pacman::setSize(GLfloat sizeX, GLfloat sizeY)
{
	x = sizeX;
	y = sizeY;
}

void Pacman::DIE() {
	glBindVertexArray(vao);
	glDeleteBuffers(1, &vbo);
	glBindVertexArray(0);
}
