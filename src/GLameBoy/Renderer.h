#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Common.h"

#pragma once
class Renderer
{
public:
	Renderer() {
		instances++;
	}

	inline static int instances = 0;
	GLFWwindow* window = nullptr;
	u8 texture[SCREEN_WIDTH * SCREEN_HEIGHT * 3] = {};

	void init();
	void draw();
	void sendTextureData();

private:
	unsigned int buildRectangle();
	unsigned int compileShaderProgram();
	void generateTexture();
};

