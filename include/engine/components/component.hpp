#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class GameObject;

#include <engine\object.hpp>

const size_t NUMBER_COMPONENTS = 8;
const enum class ComponentType {
    NON_COMPONENT = -1,
    INPUT_COMPONENT = 0,
    TRANSFORM_COMPONENT = 1,
    PHYSIC_COMPONENT = 2,
    LOGIC_COMPONENT = 3,
    CAMERA_COMPONENT = 4,
    RENDER_COMPONENT = 5,
    UI_COMPONENT = 6,
    LIGHT_COMPONENT = 7
};

class Component : public Object{
    public:
        Component(uint16_t UID, GameObject* gameObject) :
            Object(UID),
            _gameObject(gameObject) {}
        virtual void init() {}
        virtual void update(float dt) {}

        bool isEnable() const {
            return _enable;
        }

        virtual void setEnable(bool enable) {
            _enable = enable;
        }

    protected:
        GameObject* _gameObject;
    private:
        bool _enable = true;
};

#endif
