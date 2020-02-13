#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class GameObject;

#include <engine\object.hpp>


class Component : public Object{
    public:
        Component(uint16_t UID, GameObject* gameObject);
        virtual void init() = 0;
        virtual void update(float dt) = 0;
        ~Component();

        bool isEnable() const;

    protected:
        GameObject* _gameObject;
    private:
        bool _enable = true;
};

#endif
