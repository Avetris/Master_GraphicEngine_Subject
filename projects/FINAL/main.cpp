#include <engine\engine.hpp>
#include <engine\managers\gameObjectManager.hpp>
#include <engine\defaultObjects\cube.hpp>
#include <engine\defaultObjects\camera.hpp>
#include <engine\defaultObjects\quad.hpp>
#include <engine\defaultObjects\pointLight.hpp>
#include <engine\defaultObjects\sphere.hpp>
#include <engine\defaultObjects\bricks\brick.hpp>
#include "../../src/engine/defaultObjects/wall.cpp"
#include <engine\defaultObjects\bricks\simpleBrick.hpp>
#include <engine\defaultObjects\models\generator.hpp>

int main(int, char* []) {
    Engine* engine = Engine::instance();
    GameObjectManager::instance()->createGameObject<Camera>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f));
    GameObjectManager::instance()->createGameObject<PointLight>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    Window* window = Window::instance();
    float thickness = 0.5f;
    float z = -7.0f;
    GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(-3.5f, 0.0f, z), glm::vec3(0.0f), glm::vec3(thickness, 7.0f, thickness));
    GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(0.0f, 2.8f, z), glm::vec3(0.0f), glm::vec3(7.0f, thickness, thickness));
    GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(3.5f, 0.0f, z), glm::vec3(0.0f), glm::vec3(thickness, 7.0f, thickness));

  /*  GameObjectManager::instance()->createGameObject<Generator>(glm::vec3(0.0f, 0.0f, z), glm::vec3(0.0f), glm::vec3(1.0f));*/

    GameObjectManager::instance()->createBrick<SimpleBrick>(glm::vec3(0.0f, 0.0f, -7.0f));
    engine->init();
    engine->mainLoop();
    delete Engine::instance();
    return 0;
}