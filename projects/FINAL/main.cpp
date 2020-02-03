#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <engine\camera.hpp>
#include <engine\input.hpp>

Camera camera(Vector3<float>(0.0f, 7.0f, 3.0f), Vector3<float>(0.0f, 1.0f, 0.0f), -90.0f, -50.0f);

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
//
//void renderScene(const Shader& shader, const Geometry& quad, const Geometry& cube, const Geometry& sphere, const Material& material) {
//    material.use(shader);
//
//    glm::mat4 model = glm::mat4(1.0);
//    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
//    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
//    shader.set("model", model);
//    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
//    shader.set("normalMat", normalMat);
//    quad.render();
//
//    model = glm::mat4(1.0);
//    shader.set("model", model);
//    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
//    shader.set("normalMat", normalMat);
//    cube.render();
//
//    model = glm::mat4(1.0);
//    model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
//    shader.set("model", model);
//    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
//    shader.set("normalMat", normalMat);
//    sphere.render();
//}
//
//const glm::mat4 renderShadow(const SpotLight& light, const Geometry& quad, const Geometry& cube, const Geometry& sphere,
//    const Shader& s_depth, const Material& material) {
//
//    const glm::mat4 lightProjection = glm::perspective<float>(glm::radians(45.0f), 1.0f, k_shadow_near, k_shadow_far);
//    const glm::mat4 lightView = glm::lookAt(light.getPosition(), light.getDirection(), glm::vec3(0.0f, 1.0f, 0.0f));
//    const glm::mat4 lightSpaceMatrix = lightProjection * lightView;
//
//    s_depth.use(); s_depth.set("lightSpaceMatrix", lightSpaceMatrix);
//    renderScene(s_depth, quad, cube, sphere, material);
//    return lightSpaceMatrix;
//}

void render() {

}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

   /* const Shader s_phong("../projects/EJ14_02/phong.vs", "../projects/EJ14_02/blinn.fs");
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
    Input::instance()->setScrollMoveCallback(onScrollMoved);*/

    while (window->alive()) {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime);
        render();
        window->frame();
    }
    return 0;
}