#include "engine/window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <engine\gpu.hpp>
#include <engine\systems\inputSystem.hpp>
#include <engine\engine.hpp>
#include <engine\systems\cameraSystem.hpp>
#include <engine\gameObject.hpp>
#include <engine\defaultObjects\gameManager.hpp>

void onChangeFrameBufferSize(GLFWwindow*, const int32_t width, const int32_t height) noexcept {
    Window::instance()->setWidth(width);
    Window::instance()->setHeight(height);
    glViewport(0, 0, width, height);
    std::cout << width << " " << height << std::endl;
}

void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GPU::KeyId keyId = (GPU::KeyId) key;
    GPU::KeyActions keyAction = (GPU::KeyActions) action;
    if (keyAction == GPU::KeyActions::PRESS) {
        if (keyId == GPU::KeyId::ESCAPE) {
            glfwSetWindowShouldClose(window, true);
        }
        else  if (keyId == GPU::KeyId::LEFT_ALT) {
            Window::instance()->setCaptureMode();
        }
        else  if (keyId == GPU::KeyId::LEFT_CONTROL) {
            GameObject* gameObject = Engine::instance()->getSystem<CameraSystem>()->getMainCamera()->getGameObject();
            InputComponent* input = gameObject->getComponent<InputComponent>(ComponentType::INPUT_COMPONENT);
            input->setEnable(!input->isEnable());
        }
        else if (GameManager::instance()->isPaused() && keyId == GPU::KeyId::R) {
            GameManager::instance()->reset();
        }
        else if (keyId == GPU::KeyId::P) {
            GameManager::instance()->pause();
        }
        else {
            Engine::instance()->getSystem<InputSystem>()->keyPressed(keyId, keyAction);
        }
    }
    else{
        Engine::instance()->getSystem<InputSystem>()->keyPressed(keyId, keyAction);
    }
}

void onMouseMove(GLFWwindow* window, double x, double y) {
    Engine::instance()->getSystem<InputSystem>()->mouseMoved(x, y);
}

void onScrollMove(GLFWwindow* window, double x, double y) {
    Engine::instance()->getSystem<InputSystem>()->scrollMoved(x, y);
}

Window::Window() {
    if (!glfwInit()) {
        std::cout << "Error Initializing GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, "04MVID", nullptr, nullptr);
    if (!_window) {
        std::cout << "Error Creating Window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(_window);

    if (!gladLoadGL()) {
        std::cout << "Error Initializing GLAD" << std::endl;
        exit(-1);
    }

    glfwSetFramebufferSizeCallback(_window, onChangeFrameBufferSize);
    glfwSetKeyCallback(_window, onKeyPress);
    glfwSetCursorPosCallback(_window, onMouseMove);
    glfwSetScrollCallback(_window, onScrollMove);

    setCaptureMode();
}

Window::~Window() {
    glfwTerminate();
}

bool Window::alive() const {
    return !glfwWindowShouldClose(_window);
}

void Window::frame() const {
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

bool Window::keyPressed(int key) const {
    return glfwGetKey(_window, key) == GLFW_PRESS;
}

void Window::setCaptureMode() const {
    int inputMode = glfwGetInputMode(_window, GLFW_CURSOR);
    if (inputMode == GLFW_CURSOR_NORMAL) {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Window::setHeight(uint32_t height) {
    _height = height;
    glfwSetWindowSize(_window, _width, _height);
}

void Window::setWidth(uint32_t width) {
    _width = width;
    glfwSetWindowSize(_window, _width, _height);
}