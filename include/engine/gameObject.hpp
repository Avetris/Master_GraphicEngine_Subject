#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <cstdint>
#include <vector>
#include <engine\components\component.hpp>
#include <engine\managers\componentManager.hpp>
#include <engine\object.hpp>
#include <engine\handle\handle.hpp>
#include <glm/glm.hpp>

class GameObject : public Object {
    public:
        GameObject(uint16_t UID);
        GameObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
        ~GameObject();

        glm::vec3 getPosition() const;
        glm::vec3 getRotation() const;
        glm::vec3 getScale() const;
        float getRotationAngle() const;

        void setPosition(glm::vec3 position);
        void setRotation(float angle, glm::vec3 rotation);
        void setScale(glm::vec3 scale);

        template<typename Component>
        Component* addComponent(TYPE componentType);
        void removeComponent(Handle* component);
        void removeComponent(TYPE componentType);

        template<typename Component>
        Component* getComponent(TYPE componentType) const;

        template<typename Component>
        Component* getComponent() const;

        void addChildren(Handle* child);
        std::vector<Handle*> getChildren() const;
        GameObject* removeChildren(uint16_t UID);

    private:
        Handle* _parent;
        std::vector<Handle*> _children;

    private:
        glm::vec3 _position;
        glm::vec3 _rotation;
        float _rotationAngle;
        glm::vec3 _scale;
        Handle* _componentList[NUMBER_COMPONENTS];
};


template<typename Component>
inline Component* GameObject::getComponent(TYPE componentType) const
{
    Component* component = nullptr;
    if (componentType >= 0 && _componentList[componentType] != nullptr) {
        HandleManager::instance()->GetAs(_componentList[componentType], component);
    }
    return component;
}

template<typename Component>
inline Component* GameObject::getComponent<Component>() const
{
    Component* component = nullptr;
    if (componentType >= 0 && _componentList[componentType] != nullptr) {
        HandleManager::instance()->GetAs(_componentList[componentType], component);
    }
    return component;
}
#endif
