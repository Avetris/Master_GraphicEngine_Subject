#include <engine\engine.hpp>
#include <engine\managers\gameObjectManager.hpp>
#include <engine\defaultObjects\camera.hpp>
#include <engine\defaultObjects\gameManager.hpp>


int main(int, char* []) {
    Engine* engine = Engine::instance();
    Window* window = Window::instance();
    GameObjectManager::instance()->createGameObject<Camera>(glm::vec3(0.0f, 5.5f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f));
    GameManager::instance()->init();
    
    engine->init();
    engine->mainLoop();
    delete Engine::instance();
    return 0;
}
