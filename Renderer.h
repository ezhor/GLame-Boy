#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Common.h"

#pragma once
class Renderer
{
public:
	GLFWwindow* window;
	u8 texture[SCREEN_WIDTH * SCREEN_HEIGHT * 3];
	void init();
	void draw();
	void sendTextureData();

private:
	unsigned int buildRectangle();
	unsigned int compileShaderProgram();
	void generateTexture();
};

