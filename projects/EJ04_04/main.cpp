#include <glad/glad.h>

#include "engine/input.hpp"
#include "engine/window.hpp"
#include "engine/shader.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void handleInput() {
    std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();
    for (auto& key : keys) {
        std::cout << key.first << " - " << key.second << std::endl;
    }
}

uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
    float vertices[] = {
		1.0f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   0.5f, 0.5f,
		1.0f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.0f, 0.5f,


		0.0f, 0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   0.5f, 0.5f,
		0.0f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,   0.5f, 0.0f,
		-1.0f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		-1.0f, 0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   0.0f, 0.5f,
    };

    uint32_t indices[] = {
        0, 3, 1,
        1, 3, 2,

		4, 7, 5,
		5, 7, 6
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}

uint32_t createTexture(const char* path, GLint filterType) {
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterType);
	
    int width, height, nChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cout << "Error loading texture " << path << std::endl;
    }

    return texture;
}

void render(uint32_t VAO, const Shader& shader, uint32_t tex1, uint32_t tex2) {
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex1);

    shader.set("tex_1", 0);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);  // Para poder visualizar ambas texturas, primero dibujamos ambos quad con la misma textura (la primera textura)

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex2);

	shader.set("tex_1", 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // Despues, visualizamos uno de los quad con la segunda textura. De esta forma, vemos ambas texturas.
}

int main(int, char* []) {
    Window* window = Window::instance();

    stbi_set_flip_vertically_on_load(true);

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    uint32_t VBO, EBO;
    const uint32_t VAO = createVertexData(&VBO, &EBO);
    const Shader shader("../projects/EJ04_04/vertex.vs", "../projects/EJ04_04/fragment.fs");

	// Cambiamos la imagen para ver la diferencia de filters. Ademas, utilizamos la misma imagen para crear dos texturas diferentes. Cada textura tendra un filtro diferente

    uint32_t tex1 = createTexture("../assets/textures/dog.jpg", GL_NEAREST); // Textura con filtro por cercania (Se puede ver como el filtro es mas pixelado, viendose los pixeles definidos como cuadrados)
	uint32_t tex2 = createTexture("../assets/textures/dog.jpg", GL_LINEAR); // Textura con filtro lineal. (Se puede ver como el filtro de pixeles es mas lineal, viendo borroso los pixeles intermedios)

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (window->alive()) {
        handleInput();
        render(VAO, shader, tex1, tex2);
        window->frame();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteTextures(1, &tex1);

    return 0;
}