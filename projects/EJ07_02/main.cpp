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

void render(const Geometry& object, const Geometry& light, const Shader& s_phong, const Shader& s_light) {
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

    s_phong.use();
    model = glm::mat4(1.0f);
    s_phong.set("model", model);
    s_phong.set("view", view);
    s_phong.set("proj", proj);

    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);

    s_phong.set("objectColor", glm::vec3(0.6f, 0.5f, 0.2f));
    s_phong.set("lightColor", lightColor);

    s_phong.set("ambientStrength", 0.2f); // Contra mayor sea la fuerza de la luz ambiental, menos influiran el valor de las demas luces. De esta forma, con una luz ambiental muy intensa (5.0f), la pelota completa se combierte en blanca, da igual las otras luces que tenga. Por otro lado, en caso de no existr luz ambiental (0.0f), aquellas zonas en las que no exista luz, tendran un color practicamente negro.
    s_phong.set("lightPos", lightPos);

    s_phong.set("viewPos", camera.getPosition());
    s_phong.set("shininess", 64); // Al utilizar el shader de phong (el que esta puesto), si tenemos un valor de shininess muy bajo (1) podemos ver como al rededor del punto donde mayor luz llega, existe un circulo negro a su alrededor. Ademas, si cambiamos de shader a blinn, esto no ocurre ya que se utiliza una direccion halfwayDir en vez de una direccion reflejada. Por otro lado, con valores muy altos (1000) el punto de refleccion de la luz disminuye (se concentra mas), y cuando se reduce, el reflejo es mas uniforme por toda la superficie.
    s_phong.set("specularStrength", 0.6f); // Contra mayor sea la fuerza especular, mayor luz reflejara la esfera. De esta forma, valores nulos (0.0f), no tendran ningun reflejo, mientras que valores altos (5.0f) haran que la luz se refleje completamente en la esfera, creando un nuevo foco de luz.

    object.render();
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader s_phong("../projects/EJ07_02/phong.vs", "../projects/EJ07_02/phong.fs"); // Para ver el efecto de shininess con valores pequenos, se ha cambiado al shader de fragmentos de phong
    const Shader s_light("../projects/EJ07_02/light.vs", "../projects/EJ07_02/light.fs");
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