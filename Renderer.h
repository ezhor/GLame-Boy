#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma once
class Renderer
{
public:
	GLFWwindow* window;
	void init();
	void draw();

private:
	unsigned int buildRectangle();
	unsigned int compileShaderProgram();
	void generateTexture();
};

