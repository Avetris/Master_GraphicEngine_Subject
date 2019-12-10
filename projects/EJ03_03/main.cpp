#include <glad/glad.h>

#include "engine/input.hpp"
#include "engine/window.hpp"
#include "engine/shader.hpp"

#include <iostream>
#include <GLFW\glfw3.h>

void handleInput() {
	std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();
	for (auto& key : keys) {
		std::cout << key.first << " - " << key.second << std::endl;
	}
}

uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
	float vertices[] = {
		0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f
	};

	uint32_t indices[] = {
		0, 2, 1
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return VAO;
}

double x = 0, 
	   y = 0,
	   value = 0.01;
bool xUp, 
	 yUp, 
	 change = false,
	 movingX = rand() & 1,
	 movingY = rand() & 1;


void render(uint32_t VAO, const Shader& shader) {
	glClear(GL_COLOR_BUFFER_BIT);

	// Generamos lo que se va a mover en x e y aleatoriamente. Este movimiento ira de -0.5 ad 0.5 ya que fuera de estos valores no se veria el vertice afectado.

	if (movingX || !movingY) {
		if (xUp) {
			x += value;
			if (x >= 0.5) {
				xUp = false;
				change = true;
			}
		}
		else {
			x -= value;
			if (x <= -0.5) {
				xUp = true;
				change = true;
			}
		}
	}
	if (movingY || !movingX) {		
		if (yUp) {
			y += value;
			if (y >= 0.5) {
				yUp = false;
				change = true;
			}
		}
		else {
			y -= value;
			if (y <= -0.5) {
				yUp = true;
				change = true;
			}
		}
	}
	if (change) {
		movingY = rand() & 1;
		movingY = rand() & 1;
	}
	change = false;

	shader.use();
	shader.set("addPosition", x, y, 0.0f);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

int main(int, char* []) {
	Window* window = Window::instance();

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

	uint32_t VBO, EBO;
	const uint32_t VAO = createVertexData(&VBO, &EBO);
	const Shader shader("../projects/EJ03_03/vertex.vs", "../projects/EJ03_03/fragment.fs");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	while (window->alive()) {
		handleInput();
		render(VAO, shader);
		window->frame();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;
}