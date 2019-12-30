#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/input.hpp"
#include "engine/shader.hpp"
#include "engine/texture.hpp"
#include "engine/window.hpp"
#include "engine/geometry/plane.hpp"
#include "engine/geometry/cube.hpp"

#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastFrame = 0.0f;
float lastX, lastY;
bool firstMouse = true;

const glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

void handleInput(float dt) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W)) {
        camera.handleKeyboard(Camera::Movement::Forward, dt, false);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        camera.handleKeyboard(Camera::Movement::Backward, dt, false);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        camera.handleKeyboard(Camera::Movement::Left, dt, false);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        camera.handleKeyboard(Camera::Movement::Right, dt, false);
    }
}

void onKeyPress(int key, int action) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        Window::instance()->setCaptureMode(true);
    }

    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        Window::instance()->setCaptureMode(false);
    }
}

void onMouseMoved(float x, float y) {
    if (firstMouse) {
        firstMouse = false;
        lastX = x;
        lastY = y;
    }

    const float xoffset = x - lastX;
    const float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    camera.handleMouseMovement(xoffset, yoffset);
}

void onScrollMoved(float x, float y) {
    camera.handleMouseScroll(y);
}

void render(const Geometry* geometryList, const glm::mat4* modelList, const glm::vec3* viewList, const Texture* textureList, const Shader& shader, const size_t numberOfElements) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT); // Limpiamos el buffer de profundidades para volver a calculares

    for (size_t i = 0; i < numberOfElements; i++) {
        const Geometry& geom = geometryList[i];
        const Texture& tex = textureList[i];
        glm::mat4 model = modelList[i];
        glm::mat4 view = glm::translate(camera.getViewMatrix(), viewList[i]);

        shader.use();

        tex.use(shader, "tex", 0);

        shader.set("model", model);
        shader.set("view", view);
        shader.set("proj", proj);

        geom.render();
    }
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader shader("../projects/EJ06_01/vertex.vs", "../projects/EJ06_01/fragment.fs");

    const size_t numberOfElements = 11;

    // Generate the geometries. If we generate them out of main, and insert into an array, it throws a nvoglv64.dll exception in glDrawElements
    Plane plane(20.0f, 20.0f);
    Cube cube1(0.1f);
    Cube cube2(0.2f);
    Cube cube3(0.3f);
    Cube cube4(0.4f);
    Cube cube5(0.5f);
    Cube cube6(0.6f);
    Cube cube7(0.7f);
    Cube cube8(0.8f);
    Cube cube9(0.9f);
    Cube cube10(1.0f);

    Geometry* geometryList = new Geometry[numberOfElements];
    geometryList[0] = plane;
    geometryList[1] = cube1;
    geometryList[2] = cube2;
    geometryList[3] = cube3;
    geometryList[4] = cube4;
    geometryList[5] = cube5;
    geometryList[6] = cube6;
    geometryList[7] = cube7;
    geometryList[8] = cube8;
    geometryList[9] = cube9;
    geometryList[10] = cube10;


    // Generate the textures.
    const Texture* textureList = new Texture[numberOfElements]{
        Texture("../assets/textures/bricks_albedo.png", Texture::Format::RGB),
        Texture("../assets/textures/blue_blocks.jpg", Texture::Format::RGB),
        Texture("../assets/textures/bricks_arrow.jpg", Texture::Format::RGB),
        Texture("../assets/textures/blue_blocks.jpg", Texture::Format::RGB),
        Texture("../assets/textures/bricks_arrow.jpg", Texture::Format::RGB),
        Texture("../assets/textures/blue_blocks.jpg", Texture::Format::RGB),
        Texture("../assets/textures/bricks_arrow.jpg", Texture::Format::RGB),
        Texture("../assets/textures/blue_blocks.jpg", Texture::Format::RGB),
        Texture("../assets/textures/bricks_arrow.jpg", Texture::Format::RGB),
        Texture("../assets/textures/blue_blocks.jpg", Texture::Format::RGB),
        Texture("../assets/textures/bricks_arrow.jpg", Texture::Format::RGB),
    };

    // Generate the model rotations.
    const glm::mat4 modelList[numberOfElements]{
        glm::mat4(1.0f),
        glm::rotate(glm::mat4(1.0f), 15 * glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
        glm::mat4(1.0f),
        glm::rotate(glm::mat4(1.0f), 15 * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
        glm::mat4(1.0f),
        glm::rotate(glm::mat4(1.0f), 15 * glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
        glm::rotate(glm::mat4(1.0f), 15 * glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f)),
        glm::mat4(1.0f),
        glm::rotate(glm::mat4(1.0f), 15 * glm::radians(20.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
        glm::rotate(glm::mat4(1.0f), 15 * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.5f)),
        glm::mat4(1.0f),
    };
    // Generate the view positions.
    const glm::vec3 viewList[numberOfElements]{
       glm::vec3(0.0f, -0.5f, 0.0f),
       glm::vec3(1.0f, 0.0f, -1.5f),
       glm::vec3(0.0f, 0.0f, 1.5f),
       glm::vec3(0.0f, 1.0f, -1.5f),
       glm::vec3(-1.5f, 0.5f, -1.5f),
       glm::vec3(-2.0f, 1.0f, -1.5f),
       glm::vec3(-0.5f, 0.0f, -1.5f),
       glm::vec3(1.0f, 0.0f, -1.5f),
       glm::vec3(0.0f, 2.0f, -3.0f),
       glm::vec3(0.0f, 2.0f, -8.0f),
       glm::vec3(0.0f, 2.0f, 3.0f),
    };

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Habilitamos las opciones para evitar objetos mas lejanos que aparezcan antes
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Input::instance()->setKeyPressedCallback(onKeyPress);
    Input::instance()->setMouseMoveCallback(onMouseMoved);
    Input::instance()->setScrollMoveCallback(onScrollMoved);

    while (window->alive()) {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime);
        render(geometryList, modelList, viewList, textureList, shader, numberOfElements);
        window->frame();
    }

    return 0;
}