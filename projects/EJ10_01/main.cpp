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
#include "engine/geometry/teapot.hpp"
#include "engine/model.hpp"
#include <engine\light\spotLight.hpp>
#include <engine\light\directionalLight.hpp>
#include <engine\light\pointLight.hpp>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

glm::vec3 dirLightDirection(-0.2f, -1.0f, -0.3f);

bool lanternEnabled = true;

glm::vec3 pointLightPositions[] = {
    glm::vec3(4.0f, 2.0f, 0.0f),
    glm::vec3(-4.0f, 2.0f, 0.0f)
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
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        lanternEnabled = !lanternEnabled;
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

void render(const Model& object, const Sphere& light, const Shader& s_phong, const Shader& s_light, DirectionalLight& directionalLight, PointLight& pointLight, SpotLight& spotLight) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

    s_light.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pointLight.getPosition());
    model = glm::scale(model, glm::vec3(0.25f));
    s_light.set("model", model);
    s_light.set("view", view);
    s_light.set("proj", proj);
    s_light.set("lightColor", pointLight.getSpecular());

    light.render();
    
    s_phong.use();
    model = glm::mat4(1.0f);
    s_phong.set("model", model);
    s_phong.set("view", view);
    s_phong.set("proj", proj);

    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);
    s_phong.set("shininess", 32);
    directionalLight.use(s_phong);
    pointLight.use(s_phong);

    spotLight.setPosition(camera.getPosition()); 
    spotLight.setDirection(camera.getCameraDirection()); 
    spotLight.use(s_phong);

    s_phong.set("lanternEnabled", lanternEnabled);

    object.render(s_phong);
}

void rotateLight(PointLight& pointLight, float angle) {

    float s = sin(glm::radians(angle));
    float c = cos(glm::radians(angle));

    glm::vec3 pointLightPos = pointLight.getPosition();

    const float xNew = pointLightPos.x * c - pointLightPos.z * s;
    const float zNew = pointLightPos.x * s + pointLightPos.z * c;

    pointLightPos.x = xNew;
    pointLightPos.z = zNew;

    pointLight.setPosition(pointLightPos);
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader s_phong("../projects/EJ10_01/simple.vs", "../projects/EJ10_01/simple.fs");
    const Shader s_light("../projects/EJ10_01/light.vs", "../projects/EJ10_01/light.fs");
    const Sphere sphere(1.0f, 50, 50);
    const Model object("../assets/models/tower/wooden watch tower2.obj"); // Importamos un modelo de una torre de vigilancia de madera
    DirectionalLight directionalLight(
        "dirLight",
        glm::vec3(15.0f, 15.0f, 0),
        glm::vec3(0.02f, 0.02f, 0.02f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(-0.2f, -1.0f, -0.3f));
    PointLight pointLight("pointLight",
        glm::vec3(5.0f, 7.0f, 5.0f),
        glm::vec3(0.02f, 0.02f, 0.02f),
        glm::vec3(0.8f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        1.0f, 0.09f, 0.032f);
    SpotLight spotLight("spotLight",
        glm::vec3(0.0f, 3.0f, 0.0f),
        glm::vec3(0.02f, 0.02f, 0.02f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        1.0f, 0.09f, 0.032f,
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::cos(glm::radians(20.0f)),
        glm::cos(glm::radians(25.0f)));

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
        render(object, sphere, s_phong, s_light, directionalLight, pointLight, spotLight);
        window->frame();
        rotateLight(pointLight, 0.5);
    }

    return 0;
}