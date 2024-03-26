#include "glutil.h"

#include <fstream>

#include <iostream>
#include <gfx.h>

GLFWwindow* initialize_glfw_and_gl()
{ // Initialise GLFW
	if (!glfwInit())
	{
		GFX_ERROR("Failed to initialize GLFW\n");
		return nullptr;
	}

	glfwWindowHint(GLFW_SAMPLES, 2);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);         // Change to 5 if you want to use modern features! :D
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);  // To allow debug callbacks
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(768, 768, "El Pacmaño", nullptr, nullptr);
	if (window == nullptr)
	{
		GFX_ERROR("Failed to open GLFW window.\n");
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	// Initialize Glad
	if (!gladLoadGL())
	{
		GFX_ERROR("Failed to initialize GLAD\n");
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSwapInterval(1);
	return window;
}

std::string read_entire_file(const char* fp)
{
	/* Also, fopen is weird with fs::path on windows since it uses wchar_t for me, so we use ifstream */
	std::ifstream file{ fp };
	file.sync_with_stdio(false);

	std::string out = {};
	std::string line = {};
	while (std::getline(file, line))
	{
		out += line + '\n';
	}

	return out;
}

GLuint compile_shader(const char* source, GLenum type)
{
	/* Create shader, attach source code and compile it */
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	/* Check for erros */
	int err, len;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &err);

	if (!err)
	{
		/* Get log length */
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		auto log = std::string(len, '\0');

		/* Get the log text and print it */
		const char* typeString = (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");

		glGetShaderInfoLog(shader, len, &len, (GLchar*)log.data());
		fprintf(stderr, "%s Shader Compile Error:\n%s\n", typeString, log.c_str());

		/* Cleanup and return an invalid GL Name */
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint fcompile_shader(const char* filepath, GLenum type)
{
	/* Read the file contents */
	auto source = read_entire_file(filepath);

	/* Use other function to compile the extracted source, then clean up and return */
	GLuint shader = compile_shader(source.c_str(), type);

	return shader;
}

GLuint create_program(const std::vector<GLuint>& shaders)
{
	/* Create program */
	GLuint program = glCreateProgram();

	/* Attach all shaders that should be part of the program */
	for (auto shader : shaders)
	{
		glAttachShader(program, shader);
	}

	/* Link the program */
	glLinkProgram(program);

	/* Check for errors */
	int err, len;
	glGetProgramiv(program, GL_LINK_STATUS, &err);

	if (!err)
	{
		/* Get log length */
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		auto log = std::string(len, '\0');

		/* Get the log text and print it */
		glGetProgramInfoLog(program, len, &len, (GLchar*)log.data());
		fprintf(stderr, "Program Link Error:\n%s\n", log.c_str());

		/* Cleanup and return an invalid GL Name */
		glDeleteProgram(program);
		return 0;
	}

	return program;
}

#ifndef WIN32
#    define APIENTRY
#endif
void gl_debug_callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW: GFX_INFO(message); break;
	case GL_DEBUG_SEVERITY_MEDIUM: GFX_WARN(message); break;
	default: GFX_WARN(message); break;
	}
}

void create_debug_callback()
{
	glDebugMessageCallback(gl_debug_callback, nullptr);

	/* Only enable LOW -> HIGH priority debug messages. Ignore Notifications */
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, true);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, true);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0, nullptr, true);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, false);
}