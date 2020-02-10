#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <cstdint>
#include <vector>
#include <engine\object.hpp>
#include <engine\components\component.hpp>

class System : public Object{
    public:
        System();
        ~System();
        virtual void init() = 0;
        virtual void update(const float dt) = 0;

        void addComponent(Handle* component);
        void removeComponent(Component* component);

    protected:
        std::vector<Handle*> _componentList;
};

#endif
