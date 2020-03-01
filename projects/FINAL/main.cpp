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
#include <engine\defaultObjects\ball.hpp>
#include <engine\defaultObjects\bar.hpp>
#include <engine\defaultObjects\ui\uiObject.hpp>

int main(int, char* []) {
    Engine* engine = Engine::instance();
    Window* window = Window::instance();
    GameObjectManager::instance()->createGameObject<Camera>(glm::vec3(0.0f, 5.5f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f));
    GameObjectManager::instance()->createGameObject<UIObject>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f));

    
    // Creating Walls
    float z = -15.0f;
    float thickness = 0.5f;
    GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(-8.0f, 5.0f, z), glm::vec3(0.0f), glm::vec3(thickness, 12.0f, thickness));
    GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(0.0f, 10.75f, z), glm::vec3(0.0f), glm::vec3(16.0f, thickness, thickness));
    GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(8.0f, 5.0f, z), glm::vec3(0.0f), glm::vec3(thickness, 12.0f, thickness));

    // Creating ball and Bar
    Ball* ball = GameObjectManager::instance()->createGameObject<Ball>(glm::vec3(0.0f, 0.4f, z), glm::vec3(0.0f), glm::vec3(0.25f));
    GameObjectManager::instance()->createGameObject<Bar>(glm::vec3(0.0f, 0.0f, z), glm::vec3(0.0f), glm::vec3(1.0f, 0.2f, 0.2f))->setBall(ball);

  /*  GameObjectManager::instance()->createGameObject<Generator>(glm::vec3(0.0f, 0.0f, z), glm::vec3(0.0f), glm::vec3(1.0f));*/
    for (float x = -6.0f; x < 7; x++) {
        for (int y = 8; y < 18; y++) {
            GameObjectManager::instance()->createBrick<SimpleBrick>(glm::vec3(x, y * 0.5f, z));
        }
    }
    engine->init();
    engine->mainLoop();
    delete Engine::instance();
    return 0;
}