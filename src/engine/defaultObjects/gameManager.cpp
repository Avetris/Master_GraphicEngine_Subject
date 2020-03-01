#include <engine\defaultObjects\gameManager.hpp>
#include <engine\components\renderComponent\cubeComponent.hpp>
#include <engine\components\transformComponent.hpp>
#include <engine\managers\materialManager.hpp>
#include <engine\components\physicComponent.hpp>
#include <engine\managers\gameObjectManager.hpp>
#include <engine\defaultObjects\wall.hpp>
#include <engine\defaultObjects\ball.hpp>
#include <engine\defaultObjects\bar.hpp>
#include <engine\defaultObjects\bricks\simpleBrick.hpp>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <iostream>


void GameManager::init()
{
    reset();
}

void GameManager::reset()
{
    createUIObjects();
    createWalls();
    createBallAndBar();
    createBricks();
    _paused = false;
}

void GameManager::hit(int score)
{
    _score += score;
    _scoreUIObject->setScore(_score);
    if (GameObjectManager::instance()->getGameObjectNumberByTag(Brick::TAG()) <= 0) {
        _finalUIObject->showFinal(true);
    }
}


void GameManager::die()
{
    _lifes--;
    _lifesUIObject->setLifes(_lifes);
    GameObject* gm = GameObjectManager::instance()->getGameObjectByTag(Bar::TAG());
    if (gm) {
        static_cast<Bar*>(gm)->reset();
    }
    if (_lifes <= 0) {
        _finalUIObject->showFinal(false);
    }
}

bool GameManager::isPaused() {
    return _lifes <= 0 || _paused;
}

void GameManager::pause()
{
    _paused = !_paused;
}

void GameManager::createWalls() {
    float thickness = 0.5f;
    if (GameObjectManager::instance()->getGameObjectNumberByTag(Wall::TAG()) <= 0) {
        GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(-10.0f, -2.0f, _z), glm::vec3(0.0f), glm::vec3(1.0f, 1.7f, 1.0f));
        GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(0.0f, 10.75f, _z), glm::vec3(0.0f), glm::vec3(16.0f, thickness, thickness));
        GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(10.0f, -2.0f, _z), glm::vec3(0.0f), glm::vec3(1.0f, 1.7f, 1.0f));
    }

    if (GameObjectManager::instance()->getGameObjectNumberByTag("gameEnd") <= 0) {
        GameObject* gm = GameObjectManager::instance()->createGameObject<Wall>(glm::vec3(0.0f, -1.0f, _z), glm::vec3(0.0f), glm::vec3(16.0f, thickness, thickness));
        gm->setTag("gameEnd");
    }
}

void GameManager::createUIObjects() {
    if(!_scoreUIObject)
        _scoreUIObject = GameObjectManager::instance()->createGameObject<ScoreUIObject>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.5f));

    if (!_lifesUIObject)
        _lifesUIObject = GameObjectManager::instance()->createGameObject<LifesUIObject>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.5f));

    if (!_finalUIObject)
        _finalUIObject = GameObjectManager::instance()->createGameObject<FinalUIObject>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.5f));

    _score = 0;
    _lifes = 3;

    _scoreUIObject->setScore(_score);
    _lifesUIObject->setLifes(_lifes);
    _finalUIObject->hideFinal();
}

void GameManager::createBallAndBar()
{
    GameObject* ball = GameObjectManager::instance()->getGameObjectByTag(Ball::TAG());
    if(!ball)
        ball = GameObjectManager::instance()->createGameObject<Ball>(glm::vec3(0.0f, 0.4f, _z), glm::vec3(0.0f), glm::vec3(0.25f));
    if(!GameObjectManager::instance()->getGameObjectByTag(Bar::TAG()))
        GameObjectManager::instance()->createGameObject<Bar>(glm::vec3(0.0f, 0.0f, _z), glm::vec3(0.0f), glm::vec3(1.0f, 0.2f, 0.2f))->setBall(static_cast<Ball*>(ball));
}

void GameManager::createBricks()
{
    srand(time(0));  // Initialize random number generator.
    GameObject* brick = nullptr;
    while (brick = GameObjectManager::instance()->getGameObjectByTag(Brick::TAG())) {
        GameObjectManager::instance()->deleteGameObject(brick->_UID);
    }
    for (float x = -6.0f; x < 7; x++) {
        for (int y = 8; y < 18; y++) {
            uint8_t hit = glm::floor((rand() % 10) / 2) + 1;
            GameObjectManager::instance()->createBrick<SimpleBrick>(glm::vec3(x, y * 0.5f, _z), hit);
        }
    }
}
