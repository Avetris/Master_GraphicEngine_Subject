#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/input.hpp"
#include "engine/shader.hpp"
#include "engine/texture.hpp"
#include "engine/material.hpp"
#include "engine/window.hpp"
#include "engine/geometry/sphere.hpp"
#include "engine/geometry/quad.hpp"
#include "engine/geometry/teapot.hpp"
#include <engine\light\light.hpp>
#include <engine\light\pointLight.hpp>
#include <engine\light\spotLight.hpp>
#include <engine\light\directionalLight.hpp>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

glm::vec3 cubePositions[] = {
    glm::vec3(4.0f, 0.0f, 0.0f),
    glm::vec3(-4.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 4.0f),
    glm::vec3(0.0f, 0.0f, -4.0f),
    glm::vec3(4.0f, 0.0f, 4.0f),
    glm::vec3(4.0f, 0.0f, -4.0f),
    glm::vec3(-4.0f, 0.0f, 4.0f),
    glm::vec3(-4.0f, 0.0f, -4.0f),
};

glm::vec3 height = glm::vec3(0.0f, 3.0f, 0.0f);

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

    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        if (height.y < 7.0f) {
            height.y += 0.5f;
        }
    }

    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        if (height.y > 1.0f) {
            height.y -= 0.5f;
        }
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

void render(const Geometry& floor, const Geometry& object, const Geometry& light, const Shader& s_phong, const Shader& s_light, const Material& material, DirectionalLight& directionalLight, PointLight& pointLight, SpotLight& spotLight) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

    s_light.use();
    uint32_t spot = 0;
    uint32_t point = 0;
    for (const auto cubePos : cubePositions) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePos + height);
        model = glm::scale(model, glm::vec3(0.25f));
        s_light.set("model", model);
        s_light.set("view", view);
        s_light.set("proj", proj);
        s_light.set("lightColor", spot < 4 ? glm::vec3(0.0f, 0.5f, 0.0f) : glm::vec3(0.5f, 0.0f, 0.0f));

        light.render();

        spot++;
    }

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

    material.use (s_phong);

    floor.render();
    
    spot = 0;
    point = 0;
    for (const auto cubePos : cubePositions) {
        if (spot < 4) {
            spotLight.setName(("spotLight[" + std::to_string(spot) + "]").c_str());
            spotLight.setPosition(cubePos + height);
            spotLight.use(s_phong);
            spot++;
        }
        else {
            pointLight.setName(("pointLight[" + std::to_string(point) + "]").c_str());
            pointLight.setPosition(cubePos + height);
            pointLight.use(s_phong);
            point++;
        }
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePos);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        s_phong.set("model", model);

        glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
        s_phong.set("normalMat", normalMat);

        object.render();
    }
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader s_phong("../projects/EJ09_03/phong.vs", "../projects/EJ09_03/blinn.fs");
    const Shader s_light("../projects/EJ09_03/light.vs", "../projects/EJ09_03/light.fs");
    const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);
    const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);
    const Material material(t_albedo, t_specular, 32);
    DirectionalLight directionalLight(
        "dirLight",
        glm::vec3(0, 0, 0),
        glm::vec3(0.02f, 0.02f, 0.02f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(-0.2f, -1.0f, -0.3f));
    PointLight pointLight("pointLight",
            height,
            glm::vec3(0.02f, 0.02f, 0.02f),
            glm::vec3(0.2f, 0.0f, 0.0f),
            glm::vec3(0.5f, 0.0f, 0.0f),
            1.0f, 0.09f, 0.032f);
    SpotLight spotLight("spotLight",
        height,
        glm::vec3(0.02f, 0.02f, 0.02f),
        glm::vec3(0.0f, 0.5f, 0.5f),
        glm::vec3(0.0f, 0.5f, 0.0f),
        1.0f, 0.09f, 0.032f,
        glm::vec3(0.0f, -1.0f, 0.0f), 
        glm::cos(glm::radians(20.0f)),
        glm::cos(glm::radians(25.0f)));
    const Sphere sphere(1.0f, 50, 50);
    const Teapot teapot(20);
    const Quad quad(1.0f);

    Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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
        render(quad, teapot, sphere, s_phong, s_light, material, directionalLight, pointLight, spotLight);
        window->frame();
    }

    return 0;
}