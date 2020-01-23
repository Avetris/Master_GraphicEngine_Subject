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

Light* lightList[4];

glm::vec3 lightPositions[] = {
    glm::vec3(4.0f, 0.0f, 0.0f),
    glm::vec3(-4.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 4.0f),
    glm::vec3(0.0f, 0.0f, -4.0f),
    glm::vec3(4.0f, 0.0f, 4.0f),
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

void render(const Geometry& floor, const Geometry& object, const Geometry& light, const Shader& s_phong, const Shader& s_light, const Material& material, DirectionalLight& directionalLight) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

    s_light.use();
    for (size_t i = 0; i < 4; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightList[i]->getPosition());
        model = glm::scale(model, glm::vec3(0.25f));
        s_light.set("model", model);
        s_light.set("view", view);
        s_light.set("proj", proj);
        s_light.set("lightColor", lightList[i]->getSpecular());

        light.render();
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

    directionalLight.use(s_phong);
    for (size_t i = 0; i < 4; i++) {
        lightList[i]->use(s_phong);
    }

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    s_phong.set("model", model);

    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);

    object.render();
}

void rotateLight(float angle) {

    float s = sin(glm::radians(angle));
    float c = cos(glm::radians(angle));
    for (size_t i = 0; i < 4; i++) {
        glm::vec3 pos = lightList[i]->getPosition();
        const float xNew = pos.x * c - pos.z * s;
        const float zNew = pos.x * s + pos.z * c;

        pos.x = xNew;
        pos.z = zNew;

        lightList[i]->setPosition(pos);
    }
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader s_phong("../projects/EJ09_04/phong.vs", "../projects/EJ09_04/blinn.fs");
    const Shader s_light("../projects/EJ09_04/light.vs", "../projects/EJ09_04/light.fs");
    Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);
    Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);
    const Material material(&t_albedo, &t_specular, 32);

    const float height = 2.0f;
    const float far = 2.0f;

    DirectionalLight directionalLight(
        "dirLight",
        glm::vec3(0, 0, 0),
        glm::vec3(0.02f, 0.02f, 0.02f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(-0.2f, -1.0f, -0.3f));

    lightList[0] = new PointLight("pointLight[0]",
        glm::vec3(far, height, far), // posicion
        glm::vec3(0.02f, 0.02f, 0.02f), // el color ambiental de la luz. La ponemos minima para que no afecte al resultado, ya que cambiaria el color de todo
        glm::vec3(1.0f, 1.0f, 1.0f), // el valor difuso de la luz. podemos ver como la zona es más clarita, al tener un color difuso blanco
        glm::vec3(1.0f, 0.0f, 0.0f), // el color ambiental de la luz. Podemos ver que se refleja una luz roja
        1.0f, 0.045, 0.0075f); // cambiamos la atenuacion con el valor linea y el cuadratico segun los valores de las tablas (sin hacer caso a la distancia)
    lightList[1] = new PointLight("pointLight[1]",
        glm::vec3(-far, height, -far), // posicion
        glm::vec3(0.02f, 0.02f, 0.02f), // el color ambiental de la luz. La ponemos minima para que no afecte al resultado, ya que cambiaria el color de todo
        glm::vec3(0.0f, 0.0f, 0.0f), // el valor difuso de la luz. podemos ver como la zona es más oscura, al tener un color difuso negro
        glm::vec3(0.0f, 0.0f, 1.0f), // el color ambiental de la luz. Podemos ver que se refleja una luz azul
        1.0f, 0.14f, 0.07f); // cambiamos la atenuacion con el valor linea y el cuadratico segun los valores de las tablas (sin hacer caso a la distancia)
    lightList[2] = new SpotLight("spotLight[0]",
        glm::vec3(-far, height, far), // posicion
        glm::vec3(0.02f, 0.02f, 0.02f), // el color ambiental de la luz. La ponemos minima para que no afecte al resultado, ya que cambiaria el color de todo
        glm::vec3(0.0f, 0.5f, 0.5f), // la intensidad que va a tener la luz (luz difusa). La ponemos a maximo
        glm::vec3(0.0f, 0.5f, 0.0f), // el color de la luz
        1.0f, 0.07f, 0.017f, // cambiamos la atenuacion con el valor linea y el cuadratico segun los valores de las tablas (sin hacer caso a la distancia)
        glm::vec3(0.0f, -1.0f, 0.0f), // Para no mezclar las luces mucho, apuntamos la spotlight al suelo
        glm::cos(glm::radians(20.0f)), // amplitud de la luz
        glm::cos(glm::radians(25.0f))); // amplitud del desvanecimiento
    lightList[3] = new SpotLight("spotLight[1]",
        glm::vec3(far, height, -far), // posicion 
        glm::vec3(0.02f, 0.02f, 0.02f), // el color ambiental de la luz. La ponemos minima para que no afecte al resultado, ya que cambiaria el color de todo 
        glm::vec3(1.0f, 1.0f, 1.0f), // la intensidad que va a tener la luz (luz difusa). La ponemos a maximo
        glm::vec3(1.0f, 1.0f, 1.0f), // el color de la luz
        1.0f, 0.0014f, 0.000007f, // cambiamos la atenuacion con el valor linea y el cuadratico segun los valores de las tablas (sin hacer caso a la distancia)
        glm::vec3(0.0f, -1.0f, 0.0f), // Para no mezclar las luces mucho, apuntamos la spotlight al suelo
        glm::cos(glm::radians(10.0f)), // amplitud de la luz
        glm::cos(glm::radians(40.0f))); // amplitud del desvanecimiento (Se puede ver como la luz blanca, esta completamente blanca en el centro, y el area de desvanecimiento es bastante amplio)
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
        render(quad, teapot, sphere, s_phong, s_light, material, directionalLight);
        window->frame();
        rotateLight(0.5);
    }

    return 0;
}