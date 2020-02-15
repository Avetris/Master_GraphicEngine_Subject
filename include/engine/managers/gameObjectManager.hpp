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

    private:
        uint16_t _GUID;
};
template<typename GameObject>
inline GameObject* GameObjectManager::createGameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float angle)
{
    return new GameObject(_GUID++, position, rotation, scale, angle);
}
#endif
    