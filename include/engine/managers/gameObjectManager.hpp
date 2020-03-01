#ifndef __GAME_OBJECT_MANAGER_H__
#define __GAME_OBJECT_MANAGER_H__

#include <cstdint>
#include <engine\gameObject.hpp>
#include <glm/glm.hpp>

class GameObjectManager{
    public:
        static GameObjectManager* instance() {
            static GameObjectManager gomInstance;
            return &gomInstance;
        }

        template<typename GameObject>
        GameObject* createGameObject(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f), float angle = 0.0f);

        template<typename Brick>
        Brick* createBrick(glm::vec3 position, uint8_t hitNeccesaries);
        
        void deleteGameObject(uint16_t UID);
        void applyDelete();

        GameObject* getGameObjectByTag(std::string tag);
        uint16_t getGameObjectNumberByTag(std::string tag);

    private:
        uint16_t _GUID;
        std::vector<GameObject*> _objects;
        std::vector<GameObject*> _objectsToDelete;
};
template<typename GameObject>
inline GameObject* GameObjectManager::createGameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle)
{
    _objects.push_back(new GameObject(_GUID++, position, rotation, scale, angle));

    GameObject* gm = static_cast<GameObject*>(_objects.back());

    return gm;
}

template<typename Brick>
inline Brick* GameObjectManager::createBrick(glm::vec3 position, uint8_t hitNeccesaries)
{
    _objects.push_back(new Brick(_GUID++, position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.5f, 0.5f), 0.0f, hitNeccesaries));

    Brick* gm = static_cast<Brick*>(_objects.back());

    return gm;
}

inline GameObject* GameObjectManager::getGameObjectByTag(std::string tag)
{
    for (GameObject* gm : _objects) {
        if (gm != nullptr && gm->isTag(tag)) {
            return gm;
        }
    }
    return nullptr;
}

inline uint16_t GameObjectManager::getGameObjectNumberByTag(std::string tag)
{
    uint16_t number = 0;
    for (GameObject* gm : _objects) {
        if (gm != nullptr && gm->isTag(tag)) {
            number++;
        }
    }
    return number;
}

inline void GameObjectManager::deleteGameObject(uint16_t UID) {
    GameObject* gameObject = nullptr;
    for (auto it = _objects.begin(); it < _objects.end(); it++) {
        if(*it && UID == (*it)->_UID) {
            gameObject = *it;
            _objects.erase(it);
            break;
        }
    }
    if(gameObject)
        _objectsToDelete.push_back(gameObject);
}

inline void GameObjectManager::applyDelete() {
    for (GameObject* gm : _objectsToDelete) {
        delete gm;
    }
    _objectsToDelete.clear();
}
#endif
    