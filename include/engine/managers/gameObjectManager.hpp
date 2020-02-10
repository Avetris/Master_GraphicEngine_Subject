#ifndef __GAME_OBJECT_MANAGER_H__
#define __GAME_OBJECT_MANAGER_H__

#include <cstdint>
#include <glm/glm.hpp>

class GameObjectManager{
    public:
        static GameObjectManager* instance() {
            static GameObjectManager i;
            return &i;
        }

        template<typename GameObject>
        GameObject* createGameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    private:
        GameObjectManager();
        static uint16_t _GUID;
};
#endif
    