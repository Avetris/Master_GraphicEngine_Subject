#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <engine\handle\handle.hpp>
#include <engine\object.hpp>

class Component : public Object{
    public:
        Component(uint16_t UID, Handle* gameObject);
        virtual void init() = 0;
        virtual void update(float dt) = 0;
        ~Component();

        bool isEnable() const;

    protected:
        Handle* _gameObject = nullptr;
    private:
        bool _isEnable = true;
};

#endif
