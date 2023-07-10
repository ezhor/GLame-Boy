#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const char* vertexShaderSource =
"#version 330 core \n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 inputColor;"
"out vec4 vertexColor;"
"void main()\n"
"{\n"
"gl_Position = vec4(position.xyz, 1.0);\n"
"vertexColor = vec4(inputColor.xyz, 1.0);\n"
"}\0";

const char* triangleFragmentShaderSource =
"#version 330 core\n"
"in vec4 vertexColor;"
"out vec4 fragmentColor;\n"
"uniform vec4 uniformColor;"
"void main()\n"
"{\n"
"fragmentColor = uniformColor + vertexColor;"
"}\0";

const char* rectangleFragmentShaderSource =
"#version 330 core\n"
"out vec4 fragmentColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
"fragmentColor = vertexColor;"
"}\0";

bool polygonMode = true;
bool pWassPressed = false;

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		polygonMode = !polygonMode;
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode ? GL_FILL : GL_LINE);
	}
}

GLFWwindow* initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GLame Boy", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failet to initialize GLAD" << std::endl;
	}

	glfwSetKeyCallback(window, keyCallback);
	glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	return window;
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

unsigned int compileShaderProgram(const char* fragmentShaderSource) {
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

unsigned int buildTriangle() {
	float vertices[] = {
		// positions			// colors
		-0.4f, -0.4f, 0.0f,		0.5f, 0.0f, 0.0f,
		0.4f, -0.4f, 0.0f,		0.0f, 0.5f, 0.0f,
		0.0f, 0.4f, 0.0f,		0.0f, 0.0f, 0.5f
	};
	unsigned int indices[] = {
		0, 1, 2
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

unsigned int buildRectangle() {
	float vertices[] = {
		   -0.5f,  0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
		   -0.5f, -0.5f, 0.0f
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

void CalculateUniformColor(unsigned int shaderProgram) {
	float time = glfwGetTime();
	float colorValue = (sin(time) + 1.0f) / 4.0f;
	int uniformColor = glGetUniformLocation(shaderProgram, "uniformColor");
	glUseProgram(shaderProgram);
	glUniform4f(uniformColor, colorValue, colorValue, colorValue, 1.0f);
}

void draw(unsigned int VAO, unsigned int shaderProgram) {
	glBindVertexArray(VAO);
	glUseProgram(shaderProgram);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void renderLoop(GLFWwindow* window, unsigned int VAOs[], unsigned int shaderPrograms[]) {

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);		
		int size = sizeof(VAOs) / sizeof(VAOs[0]);
		for (int i = 0; i < size; i++) {
			CalculateUniformColor(shaderPrograms[1]);
			draw(VAOs[i], shaderPrograms[i]);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Renderer::run()
{
	GLFWwindow* window = initWindow();
	unsigned int VAOs[]{
		buildRectangle(),
		buildTriangle()
	};
	unsigned int shaderPrograms[]{
		compileShaderProgram(rectangleFragmentShaderSource),
		compileShaderProgram(triangleFragmentShaderSource)
	};


	renderLoop(window, VAOs, shaderPrograms);
	glfwTerminate();
}