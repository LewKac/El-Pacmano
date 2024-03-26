#define _CRT_SECURE_NO_WARNINGS

#include "glutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

//IF YOU ARE USING UNIX, UNCOMENT BOTTOM
//ALSO SWAP LINES 166/167
//#include <unistd.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../headers/pacman.h"
#include "../headers/pizza.h"
#include "../headers/wall.h"
#include "../headers/ghost.h"
#include "../headers/manager.h"

/*
TODO:
	Make destructors for everything.							- UNFINISHED
	Die function in pizza. Make into deconstructor?				- UNFINISHED
	Score/GUI													- FINISHED
	Losing life													- FINISHED
	Textures/Sprites											- FINISHED / Could be improved
	Map															- FINISHED / Could be improved
	Let classes handle VAO										- FINISHED
	Ghosts														- FINISHED
	AI															- FINISHED
	Shaders														- FINISHED
*/

/**
 * Compiles the shader used for this example and cleans up resources after compile and link
 */
GLuint make_shader()
{
	auto vshader = fcompile_shader("assets/shaders/vertex.vert", GL_VERTEX_SHADER);
	auto fshader = fcompile_shader("assets/shaders/fragment.frag", GL_FRAGMENT_SHADER);
	auto sprite_shader = create_program({ vshader, fshader });
	glDeleteShader(vshader);
	glDeleteShader(fshader);
	return sprite_shader;
}

int main(void)
{
	auto window = initialize_glfw_and_gl();
	auto shader = make_shader();
	create_debug_callback();
	glUseProgram(shader);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_KEY_ESCAPE, GL_TRUE);
	glfwSetInputMode(window, GLFW_KEY_LEFT, GL_TRUE);
	glfwSetInputMode(window, GLFW_KEY_RIGHT, GL_TRUE);
	glfwSetInputMode(window, GLFW_KEY_UP, GL_TRUE);
	glfwSetInputMode(window, GLFW_KEY_DOWN, GL_TRUE);

	//	GUI
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430 core");

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	glClearColor(0.f, 1.f, 1.f, 1.f);

	// Main Loop
	do {
		bool exitMenu = 0;
		// "Main Menu" loop
		do
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// Display Main Menu with start the game button
			ImGui::Begin("Main menu", NULL, window_flags);
			exitMenu = ImGui::Button("Start game");

			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);

			glfwSwapBuffers(window);
			glfwPollEvents();
		} while (exitMenu == 0 && glfwWindowShouldClose(window) == 0);

		int lives = 3;
		int amountPizzas = 0;
		int score = 0;

		//Create pacman
		Pacman* pac = new Pacman;

		std::vector<Ghost*> ghosts;
		std::vector<Wall*> walls;
		std::vector<Pizza*> pizzas;

		// Fills previously created vectors with game elements
		spawn(walls, pizzas, ghosts, *pac);

		// Game loop
		do
		{
			//Checks for movement of Pacman
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
				//West
				if (!checkPac(*pac, 3)) {
					pac->setDirection(3);
				}
			}
			//East
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
				if (!checkPac(*pac, 1)) {
					pac->setDirection(1);
				}
			}
			//North
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
				if (!checkPac(*pac, 0)) {
					pac->setDirection(0);
				}
			}
			//South
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
				if (!checkPac(*pac, 2)) {
					pac->setDirection(2);
				}
			}

			//Moving Mr. Pacarino here
			if (!checkPac(*pac, pac->getDirection())) {
				pac->move(shader);
			}

			//			-----		Colission checkers and point increaser		------
			for (unsigned int i = 0; i < pizzas.size(); i++) {
				if (eatPizza(*pac, *pizzas[i])) {
					pizzas[i]->DIE();
					pizzas.erase(pizzas.begin() + i);
					score += 10;
				}
			}

			//Ghosts trying to bust Pacman
			for (unsigned int i = 0; i < ghosts.size(); i++) {
				if (pacmanBusted(*pac, *ghosts[i])) {
					lives--;
					pac->teleport(spawnPosition[0], spawnPosition[1]);
					//IF YOU USE UNIX, SWAP THESE COMMANDS
					//sleep(1);
					Sleep(1000);
				}
			}

			//Keeping track of eaten pizzas
			amountPizzas = pizzas.size();

			if (!lives || !amountPizzas) {
				break;
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//			--------	Drawing all game elements here	-------

			pac->draw();

			for (unsigned int i = 0; i < pizzas.size(); i++) {
				pizzas[i]->draw();
			}

			for (unsigned int i = 0; i < walls.size(); i++) {
				walls[i]->draw();
			}

			for (unsigned int i = 0; i < ghosts.size(); i++) {
				Ghost* tempGhost = ghosts[i];
				moveGhost(tempGhost);
				ghosts[i]->move();
				ghosts[i]->draw();
			}

			//			--------	GUI		--------
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			std::string scoreBuffer = "Score: " + std::to_string(score);
			std::string livesBuffer = "Lives: " + std::to_string(lives);

			//Specify what is supposed to display
			ImGui::Begin("Stats", NULL, window_flags);
			ImGui::Text(scoreBuffer.c_str());
			ImGui::Text(livesBuffer.c_str());
			ImGui::End();

			//Show on the screen
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);

			// Swap buffers so we can see the triangle
			glfwSwapBuffers(window);

			// Listen for events (User Input)
			glfwPollEvents();
		} // Check if the ESC key was pressed or the window was closed
		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

		// If the player won/lost the game, clear the board
		delete pac;

		ghosts.clear();
		walls.clear();
		pizzas.clear();
	} while (glfwWindowShouldClose(window) == 0);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}