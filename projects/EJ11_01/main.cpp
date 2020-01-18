#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/input.hpp"
#include "engine/shader.hpp"
#include "engine/texture.hpp"
#include "engine/window.hpp"
#include "engine/geometry/sphere.hpp"
#include "engine/geometry/quad.hpp"
#include <engine\material.hpp>
#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 lightPos(4.0f, 1.0f, 0.0f);

glm::vec3 cubesPositions[] = {
    glm::vec3(4.5f, 0.0f, 4.5f),
    glm::vec3(-4.5f, 0.0f, 4.5f),
    glm::vec3(4.5f, 0.0f, -4.5f),
    glm::vec3(-4.5f, 0.0f, -4.5f)
};

glm::vec3 grassPositions[] = {
    glm::vec3(4.5f, 0.0f, 3.9f),
    glm::vec3(-4.5f, 0.0f, 3.9f),
    glm::vec3(4.5f, 0.0f, -3.9f),
    glm::vec3(-4.5f, 0.0f, -3.9f)
};
float grassRotations[] = {
    glm::radians(180.0f),
    glm::radians(180.0f),
    0.0f,
    0.0f
};

float lastFrame = 0.0f;
float lastX, lastY;
bool firstMouse = true;

void handleInput(float dt) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W)) {
        camera.handleKeyboard(Camera::Movement::Forward, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        camera.handleKeyboard(Camera::Movement::Backward, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        camera.handleKeyboard(Camera::Movement::Left, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        camera.handleKeyboard(Camera::Movement::Right, dt);
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

void render(const Geometry& floor, const Geometry& object, const Shader& s_phong, const Shader& s_blend, 
    const Material& m_floor, const Texture* t_wood, const Texture& t_grass) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

    s_phong.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
    s_phong.set("model", model);
    s_phong.set("view", view);
    s_phong.set("proj", proj);

    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);

    s_phong.set("viewPos", camera.getPosition());

    s_phong.set("light.direction", -0.2f, -1.0f, -0.3f);
    s_phong.set("light.ambient", 0.1f, 0.1f, 0.1f);
    s_phong.set("light.diffuse", 0.5f, 0.5f, 0.5f);
    s_phong.set("light.specular", 1.0f, 1.0f, 1.0f);

    m_floor.use(s_phong);

    floor.render();

    for (size_t i = 0; i < sizeof(cubesPositions) / sizeof(glm::vec3); ++i) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubesPositions[i]);
        s_phong.set("model", model);

        normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
        s_phong.set("normalMat", normalMat);
        t_wood[i].use(s_phong, "material.diffuse", 0);
        s_phong.set("material.shininess", 32);

        object.render();
    }

    s_blend.use();
    for (size_t i = 0; i < sizeof(grassPositions) / sizeof(glm::vec3); ++i) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, grassPositions[i]);
        model = glm::rotate(model, grassRotations[i], glm::vec3(0.0f, 1.0f, 0.0f));
        s_blend.set("model", model);
        s_blend.set("view", view);
        s_blend.set("proj", proj);

        t_grass.use(s_blend, "texture1", 0);
        floor.render();
    }

}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader s_phong("../projects/EJ11_01/phong.vs", "../projects/EJ11_01/blinn.fs");
    const Shader s_blend("../projects/EJ11_01/blend.vs", "../projects/EJ11_01/blend.fs");
    const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);
    const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);
    const Texture t_grass("../assets/textures/grass.png", Texture::Format::RGBA);
    const Cube cube(1.0f);
    const Quad quad(1.0f);
    const Material m_floor(t_albedo, t_specular, 32);
    const Texture t_wood[] = {
        Texture("../assets/textures/wood1.jpg", Texture::Format::RGB),
        Texture("../assets/textures/wood2.jpg", Texture::Format::RGB),
        Texture("../assets/textures/wood3.jpg", Texture::Format::RGB),
        Texture("../assets/textures/wood4.jpg", Texture::Format::RGB)
    };

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Input::instance()->setKeyPressedCallback(onKeyPress);
    Input::instance()->setMouseMoveCallback(onMouseMoved);
    Input::instance()->setScrollMoveCallback(onScrollMoved);

    while (window->alive()) {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime);
        render(quad, cube, s_phong, s_blend, m_floor, t_wood, t_grass);
        window->frame();
    }

    return 0;
}