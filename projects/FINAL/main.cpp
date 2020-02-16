#include <engine\engine.hpp>
#include <engine\managers\gameObjectManager.hpp>
#include <engine\defaultObjects\cube.hpp>
#include <engine\defaultObjects\camera.hpp>
#include <engine\defaultObjects\quad.hpp>
#include <engine\defaultObjects\pointLight.hpp>
#include <engine\defaultObjects\sphere.hpp>

int main(int, char* []) {
    Engine* engine = Engine::instance();
    GameObjectManager::instance()->createGameObject<Camera>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(3.0f));

    GameObjectManager::instance()->createGameObject<PointLight>(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    GameObjectManager::instance()->createGameObject<PointLight>(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));


    GameObjectManager::instance()->createGameObject<Quad>(glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(10.0f), -90.0f);
    GameObjectManager::instance()->createGameObject<Cube>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    engine->init();
    engine->mainLoop();
    delete Engine::instance();
    return 0;
}