#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

class Component;

#include <vector>
#include <engine\managers\componentManager.hpp>
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

        template<class T>
        T* addComponent(TYPE componentType);
        void removeComponent(Component* component);
        void removeComponent(TYPE componentType);

        template<class T>
        T* getComponent(TYPE componentType) const;

        template<class T>
        T* getComponent() const;

        void addChildren(GameObject* child);
        std::vector<GameObject*> getChildren() const;
        GameObject* removeChildren(uint16_t UID);

    private:
        GameObject* _parent = nullptr;
        std::vector<GameObject*> _children;

    private:
        glm::vec3 _position;
        glm::vec3 _rotation;
        float _rotationAngle;
        glm::vec3 _scale;
        Component* _componentList[NUMBER_COMPONENTS] = { nullptr };
};


template<class T>
 T* GameObject::addComponent(TYPE componentType)
{
    T* component = dynamic_cast<T*>(_componentList[componentType]);
    if (component == nullptr) {
        component = ComponentManager::instance()->createComponent<T>(this);
        _componentList[componentType] = component;
    }
    return component;
}

template<class T>
T* GameObject::getComponent(TYPE componentType) const
{
    return dynamic_cast<T*>(_componentList[componentType]);
}

template<class T>
T* GameObject::getComponent() const
{
    T* output;
    for (auto component : _systemList) {
        output = dynamic_cast<T*>(component);
        if (output) {
            break;
        }
    }
    return output;
}
#endif
