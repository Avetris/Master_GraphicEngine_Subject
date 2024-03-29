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

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 lightPos(2.0f, 1.0f, 2.0f);

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


void setMaterialColor(const Shader& s_phong, const glm::mat4 model,
                      const float ambienR, const float ambientG, const float ambientB,
                      const float diffuseR, const float diffuseG, const float diffuseB,
                      const float specularR, const float specularG, const float specularB,
                      const int shininess) {
    s_phong.set("model", model);
    s_phong.set("normalMat", glm::inverse(glm::transpose(glm::mat3(model))));

    s_phong.set("material.ambient", ambienR, ambientG, ambientB);
    s_phong.set("material.diffuse", diffuseR, diffuseG, diffuseB);
    s_phong.set("material.specular", specularR, specularG, specularB);
    s_phong.set("material.shininess", shininess);
}


void render(const Geometry& object, const Geometry& light, const Shader& s_phong, const Shader& s_light) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::vec3 lightDiffuse(0.5f, 0.5f, 0.5f);

    s_light.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.25f));
    s_light.set("model", model);
    s_light.set("view", view);
    s_light.set("proj", proj);
    s_light.set("lightColor", lightDiffuse);

    light.render();

    s_phong.use();
    s_phong.set("view", view);
    s_phong.set("proj", proj);

    s_phong.set("light.position", lightPos);
    s_phong.set("light.ambient", 0.1f, 0.1f, 0.1f);
    s_phong.set("light.diffuse", lightDiffuse);
    s_phong.set("light.specular", 1.0f, 1.0f, 1.0f);

    s_phong.set("viewPos", camera.getPosition());

    // SPHERE 1 - SILVER
    setMaterialColor(s_phong, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2)),
        0.19225f, 0.19225f, 0.19225f,
        0.50754f, 0.50754f, 0.50754f,
        0.508273f, 0.508273f, 0.508273f,
        4);
    object.render();
    
    // SPHERE 2 - ESMERALD
    setMaterialColor(s_phong, glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -2 + 2 * sqrt(3))),
                    0.0215f, 0.1745f, 0.0215f,
                    0.07568f, 0.61424f, 0.07568f,
                    0.633f, 0.727811f, 0.633f,
                    6);
    object.render();
    
    // SPHERE 3  - OBSIDIAN
    setMaterialColor(s_phong, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2 + 4 * sqrt(3))),
        0.05375f, 0.05f, 0.06625f, 
        0.18275f, 0.17f, 0.22525f, 
        0.332741f, 0.328634f, 0.346435f,
        3);
    object.render();

    // SPHERE 4 - CYAN PLASTIC
    setMaterialColor(s_phong, glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, -2 + 4 * sqrt(3))),
        0.0f, 0.1f, 0.06f,
        0.0f, 0.50980392f, 0.50980392f,
        0.50196078f, 0.50196078f, 0.50196078f,
        25);
    object.render();

    // SPHERE 5 - RUBY
    setMaterialColor(s_phong, glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.0f, -2 + 2 * sqrt(3))),
        0.1745f, 0.01175f, 0.01175f,
        0.61424f, 0.04136f, 0.04136f,
        0.727811f, 0.626959f, 0.626959f,
        6);
    object.render();

    // SPHERE 6 - GOLD
    setMaterialColor(s_phong, glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, -2)),
        0.24725f, 0.1995f, 0.0745f,
        0.75164f, 0.60648f, 0.22648f,
        0.628281f, 0.555802f, 0.366065f,
        4);
    object.render();
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader s_phong("../projects/EJ08_01/phong.vs", "../projects/EJ08_01/blinn.fs");
    const Shader s_light("../projects/EJ08_01/light.vs", "../projects/EJ08_01/light.fs");
    const Sphere sphere(1.0f, 50, 50);

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
        render(sphere, sphere, s_phong, s_light);
        window->frame();
    }

    return 0;
}