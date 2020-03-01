#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

class Component;

#include <vector>
#include <glm/glm.hpp>
#include <engine\managers\componentManager.hpp>

class GameObject : public Object {
    public:
        GameObject(uint16_t UID);
        GameObject(uint16_t UID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float rotationAngle);
        ~GameObject();

        glm::vec3 getPosition() const;
        glm::vec3 getRotation() const;
        glm::vec3 getScale() const;
        float getRotationAngle() const;

        void setPosition(glm::vec3 position);
        void setRotation(float angle, glm::vec3 rotation);
        void setScale(glm::vec3 scale);

        template<class T>
        T* addComponent(ComponentType componentType);
        void removeComponent(Component* component);
        void removeComponent(ComponentType componentType);

        template<class T>
        T* getComponent(ComponentType componentType) const;

        template<class T>
        T* getComponent() const;

        void enableComponent(ComponentType componentType, bool enable);

        void addChildren(GameObject* child);
        std::vector<GameObject*> getChildren() const;
        GameObject* removeChildren(uint16_t UID);
        void resetPosition();

        void setTag(std::string tag);
        bool isTag(std::string tag);


        // TODO remove from here Input Control
        virtual void onKeyPressed(GPU::KeyId key, GPU::KeyActions action) {}
        virtual void onMouseMoved(float x, float y) {}
        virtual void onScrollMoved(float x, float y) {}
        virtual void onKeyDown(GPU::KeyId keyId) {}
        virtual void onKeyUp(GPU::KeyId key) {}
        virtual void onKeyRepeat(GPU::KeyId key) {}
        virtual void onUpdateInput(float dt) {}
        
        // TODO remove from here Collision
        virtual void onCollision(GameObject* collisionGameObject) {}

    protected:
        std::string _tag = "";

    private:
        glm::vec3 _originalPosition;
        GameObject* _parent = nullptr;
        std::vector<GameObject*> _children;

        glm::vec3 _position;
        glm::vec3 _rotation;
        float _rotationAngle = 0.0f;
        glm::vec3 _scale;
        Component* _componentList[NUMBER_COMPONENTS] = { nullptr };
};


template<class T>
 T* GameObject::addComponent(ComponentType componentType)
{
    T* component = dynamic_cast<T*>(_componentList[(int) componentType]);
    if (component == nullptr) {
        component = ComponentManager::instance()->createComponent<T>(this);
        _componentList[(int) componentType] = component;
    }
    return component;
}

template<class T>
T* GameObject::getComponent(ComponentType componentType) const
{
    return dynamic_cast<T*>(_componentList[(int) componentType]);
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
