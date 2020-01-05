#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/input.hpp"
#include "engine/window.hpp"

#include <iostream>

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

uint32_t createProgram(bool firstTriangle) {
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main() {\n"
		"    gl_Position = vec4(aPos, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"    FragColor = vec4(0.2, 1.0, 0.2, 1.0);\n"
		"}\0";

	if (!firstTriangle) {
		fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main() {\n"
			"    FragColor = vec4(1.0, 0.1, 0.2, 1.0);\n"
			"}\0";
	}


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

uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,

		-0.5f, 0.5f, 0.0f, //Creamos los 3 nuevos v�rtices. Al utilizar glDrawElements, el vertice que comparten no lo duplicamos.
		-1.0f, -0.5f, 0.0f,
	};

	uint32_t indices[] = {
		0, 1, 2,
		3, 4, 1, //Creamos los indices del nuevo vertice
	};

	uint32_t VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return VAO;
}


void render(uint32_t VAO, uint32_t program1, uint32_t program2) {
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program1);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Se pintan todos los vertices.
	
	glUseProgram(program2);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); //Se pintan solo los 3 primeros vertices. De esta forma, se ven dos triangulos con diferente color.
}

int main(int, char* []) {
	Window* window = Window::instance();

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

	uint32_t VBO, EBO;
	const uint32_t VAO = createVertexData(&VBO, &EBO);
	const uint32_t program1 = createProgram(true);
	const uint32_t program2 = createProgram(false);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	while (window->alive()) {
		render(VAO, program1, program2);
		window->frame();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteProgram(program1);
	glDeleteProgram(program2);

	return 0;
}