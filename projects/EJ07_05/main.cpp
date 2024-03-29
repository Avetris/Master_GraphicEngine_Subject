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
glm::vec3 lightPos(4.0f, 1.0f, 0.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

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

void renderWithShader(const Geometry& sphere, const Shader& shader,
                       glm::vec3 objectColor, float ambientStrength, int shininess, float specularStrength, 
                       glm::mat4& model, glm::mat4& proj, glm::mat4& view, glm::vec3& viewPos, glm::mat3& normalMat) {
    shader.use();
    shader.set("model", model);
    shader.set("view", view);
    shader.set("proj", proj);

    shader.set("normalMat", normalMat);

    shader.set("objectColor", objectColor);
    shader.set("lightColor", lightColor);

    shader.set("ambientStrength", ambientStrength);
    shader.set("lightPos", lightPos);

    shader.set("viewPos", viewPos);
    shader.set("shininess", shininess);
    shader.set("specularStrength", specularStrength);

    sphere.render();
}

void render(const Geometry& sphere, const Geometry& light, const Shader& s_flat, const Shader& s_gourand, const Shader& s_phong, const Shader& s_light) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);


    s_light.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.25f));
    s_light.set("model", model);
    s_light.set("view", view);
    s_light.set("proj", proj);
    s_light.set("lightColor", lightColor);

    light.render();

    glm::vec3 objectColor(0.6f, 0.5f, 0.2f);
    float ambientStrength = 0.2f, specularStrength = 0.6f;
    int shininess = 64;
    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));

    renderWithShader(sphere, s_flat, objectColor, ambientStrength, shininess, specularStrength,
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f)), proj, view, camera.getPosition(), normalMat);
    renderWithShader(sphere, s_gourand, objectColor, ambientStrength, shininess, specularStrength,
        glm::mat4(1.0f), proj, view, camera.getPosition(), normalMat);
    renderWithShader(sphere, s_phong, objectColor, ambientStrength, shininess, specularStrength,
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)), proj, view, camera.getPosition(), normalMat);
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader s_flat("../projects/EJ07_05/flat.vs", "../projects/EJ07_05/flat.fs");
    const Shader s_gourand("../projects/EJ07_05/gourand.vs", "../projects/EJ07_05/gourand.fs");
    const Shader s_phong("../projects/EJ07_05/phong.vs", "../projects/EJ07_05/phong.fs");
    const Shader s_light("../projects/EJ07_05/light.vs", "../projects/EJ07_05/light.fs");
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
        render(sphere, sphere, s_flat, s_gourand, s_phong, s_light);
        window->frame();
    }

    return 0;
}