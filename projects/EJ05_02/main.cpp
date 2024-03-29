#include <glad/glad.h>

#include "engine/window.hpp"
#include "engine/shader.hpp"

#include "engine/texture.hpp"
#include "engine/geometry/cube.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

void handleInput() {/*Intentionally Left BLank*/ }

void render(const Geometry& geom, const Shader& shader, Texture& tex) {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model);
    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4

    geom.render();
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader shader("../projects/EJ05_02/vertex.vs", "../projects/EJ05_02/fragment.fs");
    // Generate ubs array with the position of each element.
    float uvs[] = {
            0.5f, 0.75f, // front
            0.25f, 0.75f,
            0.25f, 0.5f,
            0.5f, 0.5f,

            0.5f, 0.5f, // bottom
            0.25f, 0.5f,
            0.25f, 0.25f,
            0.5f, 0.25f,

            0.75f, 0.5f,   //back
            1.0f, 0.5f,
            1.0f, 0.75f,
            0.75f, 0.75f,

            0.5f, 1.0f, // top
            0.25f, 1.0f,
            0.25f, 0.75f,
            0.5f, 0.75f,

            0.25f, 0.75f, // left
            0.0f, 0.75f,
            0.0f, 0.5f,
            0.25f, 0.5f,

            0.75f, 0.75f, // right
            0.5f, 0.75f,
            0.5f, 0.5f,
            0.75f, 0.5f,
    };
    const Cube cube(1.0f, uvs); // It is called the new cube's constructor with the uvs setted.

    Texture tex("../assets/textures/EJ05.02_cube_uv_b.jpg", Texture::Format::RGB);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (window->alive()) {
        handleInput();
        render(cube, shader, tex);
        window->frame();
    }

    return 0;
}