#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/input.hpp"
#include "engine/window.hpp"

#include <iostream>

void handleInput() {
	std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();
	for (auto& key : keys) {
		std::cout << key.first << " - " << key.second << std::endl;
	}
}

bool checkShader(uint32_t shader) {
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "Error Compiling Shader " << infoLog << std::endl;
		return false;
	}
	return true;
}

bool checkProgram(uint32_t program) {
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "Error Linking Program " << infoLog << std::endl;
		return false;
	}
	return true;
}

uint32_t createProgram() {
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main() {\n"
		"    gl_Position = vec4(aPos, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"    FragColor = vec4(0.6, 0.6, 0.1, 1.0);\n"
		"}\0";

	const uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	checkShader(vertexShader);

	const uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	checkShader(fragmentShader);

	const uint32_t program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	checkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

uint32_t createVertexData(uint32_t* VBO, bool firstTriangle) {

	uint32_t indices[] = {
		0, 2, 1,
		3, 5, 4, //Creamos los indices del nuevo vertice
	};

	uint32_t VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);

	if (firstTriangle) {
		float vertices[] = {
			0.0f, -0.5f, 0.0f,
			1.0f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
	else {
		float vertices[] = {
			-1.0f, -0.5f, 0.0f, //Creamos los 3 nuevos vértices. Al utilizar glDrawArrays, no podemos utilizar el vertice que comparten.
			0.0f, -0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
		
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}


void render(uint32_t VAO1, uint32_t VAO2, uint32_t program) {
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glBindVertexArray(VAO1);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Pintamos los 3 vertices del primer triangulo
	glBindVertexArray(VAO2);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Pintamos los 3 vertices del segundo triangulo
}

int main(int, char* []) {
	Window* window = Window::instance();

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

	uint32_t VBO1, VBO2;
	const uint32_t VAO1 = createVertexData(&VBO1, true); // Generamos los vertices e indices para el primer triangulo
	const uint32_t VAO2 = createVertexData(&VBO2, false); // Generamos los vertices e indices para el segundo triangulo
	const uint32_t program = createProgram();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	while (window->alive()) {
		handleInput();
		render(VAO1, VAO2, program);
		window->frame();
	}

	glDeleteVertexArrays(1, &VAO1);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO1);
	glDeleteBuffers(1, &VBO2);

	glDeleteProgram(program);

	return 0;
}