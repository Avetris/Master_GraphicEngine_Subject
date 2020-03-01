#include <engine\engine.hpp>
#include <engine\managers\gameObjectManager.hpp>
#include <engine\defaultObjects\camera.hpp>
#include <engine\defaultObjects\gameManager.hpp>
#include <engine\defaultObjects\pointLight.hpp>
#include <engine\defaultObjects\quad.hpp>
#include <engine\defaultObjects\cube.hpp>
#include <engine\defaultObjects\models\generator.hpp>


int main(int, char* []) {
    Engine* engine = Engine::instance();
    Window* window = Window::instance();
    GameObjectManager::instance()->createGameObject<Camera>(glm::vec3(0.0f, 5.5f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f));
    GameManager::instance()->init();

   /* GameObjectManager::instance()->createGameObject<Quad>(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(10.0f), -90.0f);
    GameObjectManager::instance()->createGameObject<Cube>(glm::vec3(0.0f, 1.0f, -10.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    GameObjectManager::instance()->createGameObject<PointLight>(glm::vec3(5.0f, 6.0f, -12.0f), glm::vec3(0.0f), glm::vec3(1.0f));*/

    GameObjectManager::instance()->createGameObject<Bomb>(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    
    engine->init();
    engine->mainLoop();
    delete Engine::instance();
    return 0;
}
