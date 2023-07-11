#include <iostream>
#include "Renderer.h"
#include "Common.h"

#define SCREEN_SCALE 4
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define SCALED_SCREEN_WIDTH SCREEN_WIDTH * SCREEN_SCALE
#define SCALED_SCREEN_HEIGHT SCREEN_HEIGHT * SCREEN_SCALE

u8 texture[SCREEN_WIDTH * SCREEN_HEIGHT * 3];
bool polygonMode = true;
bool pWassPressed = false;
unsigned int background;
unsigned int shaderProgram;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		polygonMode = !polygonMode;
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode ? GL_FILL : GL_LINE);
	}
}

void framebufferSizeCallback(GLFWwindow* window, int windowWidth, int windowHeight) {
	int width = windowHeight * SCREEN_WIDTH / SCREEN_HEIGHT;
	glViewport((windowWidth - width) / 2, 0, width, windowHeight);
}

void Renderer::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(SCALED_SCREEN_WIDTH, SCALED_SCREEN_HEIGHT, "GLame Boy", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failet to initialize GLAD" << std::endl;
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glViewport(0, 0, SCALED_SCREEN_WIDTH, SCALED_SCREEN_HEIGHT);
	background = buildRectangle();
	shaderProgram = compileShaderProgram();
	generateTexture();
}

void checkShaderCompilationError(int shader) {
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader compilation failed:\n " << infoLog << std::endl;
	}
}

unsigned int compileShader(const char* shaderSource, GLenum shaderType) {
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	checkShaderCompilationError(shader);
	return shader;
}

void checkShaderProgramLinkingError(int shaderProgram) {
	int success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Shader program linking failed:\n " << infoLog << std::endl;
	}
}

void Renderer::generateTexture() {
	unsigned int textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
}

unsigned int Renderer::compileShaderProgram() {
	const char* vertexShaderSource =
		"#version 330 core \n"
		"layout (location = 0) in vec3 position;\n"
		"out vec2 uvs;"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.xyz, 1.0);\n"
		"uvs = vec2((position.x + 1.0)/ 2.0, (position.y + 1.0) / 2.0);\n"
		"}\0";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"in vec2 uvs;\n"
		"out vec4 fragmentColor;\n"
		"uniform sampler2D inputTexture;\n"
		"void main()\n"
		"{\n"
		"fragmentColor = texture(inputTexture, uvs);"
		"}\0";
	unsigned int vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	checkShaderProgramLinkingError(shaderProgram);
	return shaderProgram;
}

unsigned int Renderer::buildRectangle() {
	float vertices[] = {
		   -1.0f,  1.0f, 0.0f,	// top left
			1.0f,  1.0f, 0.0f,	// top right
			1.0f, -1.0f, 0.0f,	// bottom right
		   -1.0f, -1.0f, 0.0f	// bottom left
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);
	glBindVertexArray(background);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(window);
	glfwPollEvents();
}