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
#include <iostream>
#include <engine\fbo\shadow.hpp>
#include <engine\material.hpp>
#include <engine\light\spotLight.hpp>

Camera camera(glm::vec3(0.0f, 7.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -50.0f);

const uint32_t k_shadow_height = 1024;
const uint32_t k_shadow_width = 1024;
const float k_shadow_near = 1.0f;
const float k_shadow_far = 10.5f;

SpotLight spotLight("spotLight[0]",
    glm::vec3(3.0f, 3.0f, 3.0f),
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    1.0f, 0.09f, 0.032f,
    -glm::vec3(3.0f, 3.0f, 3.0f),
    glm::cos(glm::radians(20.0f)),
    glm::cos(glm::radians(25.0f)));

SpotLight spotLight2("spotLight[1]",
    glm::vec3(-3.0f, 3.0f, -3.0f),
    glm::vec3(0.02f, 0.02f, 0.02f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    1.0f, 0.09f, 0.032f,
    -glm::vec3(-3.0f, 3.0f, -3.0f),
    glm::cos(glm::radians(20.0f)),
    glm::cos(glm::radians(25.0f)));

float lastFrame = 0.0f;
float lastX, lastY;
bool firstMouse = true;

void rotateHorizontal(SpotLight& light, float angle) {
    float s = sin(glm::radians(angle));
    float c = cos(glm::radians(angle));
    glm::vec3 pos = light.getPosition();
    const float xNew = pos.x * c - pos.z * s;
    const float zNew = pos.x * s + pos.z * c;
    pos.x = xNew;
    pos.z = zNew;

    light.setPosition(pos);
    light.setDirection(-pos);
}

void rotateVertical(SpotLight& light, float angle) {

    float s = sin(glm::radians(angle));
    float c = cos(glm::radians(angle));
    glm::vec3 pos = light.getPosition();
    const float zNew = pos.z * c - pos.y * s;
    const float yNew = pos.z * s + pos.y * c;

    if (yNew > 0) {
        pos.z = zNew;
        pos.y = yNew;

        light.setPosition(pos);
        light.setDirection(-pos);
    }
}

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

    if (input->isKeyPressed(GLFW_KEY_LEFT) || input->isKeyPressed(GLFW_KEY_RIGHT)) {
        rotateHorizontal(spotLight, input->isKeyPressed(GLFW_KEY_LEFT) ? 5.0f : -5.0f);
    }
    if (input->isKeyPressed(GLFW_KEY_UP) || input->isKeyPressed(GLFW_KEY_DOWN)) {
        rotateVertical(spotLight, input->isKeyPressed(GLFW_KEY_UP) ? 5.0f : -5.0f);
    }
    if (input->isKeyPressed(GLFW_KEY_KP_4) || input->isKeyPressed(GLFW_KEY_KP_6)) {
        rotateHorizontal(spotLight2, input->isKeyPressed(GLFW_KEY_KP_4) ? 5.0f : -5.0f);
    }
    if (input->isKeyPressed(GLFW_KEY_KP_2) || input->isKeyPressed(GLFW_KEY_KP_8)) {
        rotateVertical(spotLight2, input->isKeyPressed(GLFW_KEY_KP_2) ? 5.0f : -5.0f);
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

void renderScene(const Shader& shader, const Geometry& quad, const Geometry& cube, const Geometry& sphere, const Material& material) {
    material.use(shader);

    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
    shader.set("model", model);
    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    shader.set("normalMat", normalMat);
    quad.render();

    model = glm::mat4(1.0);
    shader.set("model", model);
    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    shader.set("normalMat", normalMat);
    cube.render();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
    shader.set("model", model);
    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    shader.set("normalMat", normalMat);
    sphere.render();
}

const glm::mat4 renderShadow(const SpotLight& light, const Geometry& quad, const Geometry& cube, const Geometry& sphere,
    const Shader& s_depth, const Material& material) {

    const glm::mat4 lightProjection = glm::perspective<float>(glm::radians(45.0f), 1.0f, k_shadow_near, k_shadow_far);
    const glm::mat4 lightView = glm::lookAt(light.getPosition(), light.getDirection(), glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    s_depth.use(); s_depth.set("lightSpaceMatrix", lightSpaceMatrix);
    renderScene(s_depth, quad, cube, sphere, material);
    return lightSpaceMatrix;
}

void render(const Geometry& quad, const Geometry& cube, const Geometry& sphere,
    const Shader& s_phong, const Shader& s_depth, const Shader& s_debug, const Shader& s_light, 
    const Material& material, const ShadowFBO& fbo) {

    //FIRST PASS
    fbo.render();
    glm::mat4 lightSpaceMatrix = renderShadow(spotLight, quad, cube, sphere, s_depth, material);
    glm::mat4 lightSpaceMatrix2 = renderShadow(spotLight2, quad, cube, sphere, s_depth, material);

    //SECOND PASS
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::instance()->getWidth(), Window::instance()->getHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(Window::instance()->getWidth()) / Window::instance()->getHeight(), 0.1f, 100.0f);
    
    s_light.use();
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, spotLight.getPosition());
    s_light.set("model", model);
    s_light.set("view", view);
    s_light.set("proj", proj);
    s_light.set("lightColor", 1.0f, 1.0f, 1.0f);
    sphere.render();

    model = glm::mat4(1.0);
    model = glm::translate(model, spotLight2.getPosition());
    s_light.set("model", model);
    s_light.set("view", view);
    s_light.set("proj", proj);
    s_light.set("lightColor", 1.0f, 1.0f, 1.0f);
    sphere.render();

    s_phong.use();

    s_phong.set("view", view);
    s_phong.set("proj", proj);

    s_phong.set("viewPos", camera.getPosition());

    spotLight.use(s_phong);
    spotLight2.use(s_phong);
     
    material.use(s_phong);

    s_phong.set("lightSpaceMatrix[0]", lightSpaceMatrix);

    s_phong.set("lightSpaceMatrix[1]", lightSpaceMatrix2);

    fbo.renderTexture(s_phong);

    renderScene(s_phong, quad, cube, sphere, material);

   /* glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::instance()->getWidth(), Window::instance()->getHeight());
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    s_debug.use();
    fbo.renderTexture(s_debug);
    s_debug.set("depthMap", 0);

    quad.render();*/
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader s_phong("../projects/EJ14_02/phong.vs", "../projects/EJ14_02/blinn.fs");
    const Shader s_depth("../projects/EJ14_02/depth.vs", "../projects/EJ14_02/depth.fs");
    const Shader s_debug("../projects/EJ14_02/debug.vs", "../projects/EJ14_02/debug.fs");
    const Shader s_light("../projects/EJ14_02/light.vs", "../projects/EJ14_02/light.fs");
    Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);
    Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);
    const Material material(&t_albedo, &t_specular, 32);
    const Quad quad(2.0f);
    const Cube cube(1.0f);
    const Sphere sphere(1.0f, 25, 25);

    const ShadowFBO fbo(k_shadow_width, k_shadow_height);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Input::instance()->setKeyPressedCallback(onKeyPress);
    Input::instance()->setMouseMoveCallback(onMouseMoved);
    Input::instance()->setScrollMoveCallback(onScrollMoved);

    while (window->alive()) {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime);
        render(quad, cube, sphere, s_phong, s_depth, s_debug, s_light, material, fbo);
        window->frame();
    }
    return 0;
}