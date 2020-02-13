#include <engine\engine.hpp>
#include <engine\managers\gameObjectManager.hpp>
#include <engine\defaultObjects\cube.hpp>

int main(int, char* []) {
    Engine* engine = Engine::instance();
    engine->init();
    GameObjectManager::instance()->createGameObject<Cube>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    engine->mainLoop();
    delete[] Engine::instance();
    return 0;
}