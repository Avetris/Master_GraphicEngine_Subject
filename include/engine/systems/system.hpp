#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <cstdint>
#include <vector>
#include <engine\object.hpp>
#include <engine\components\component.hpp>

class System{
    public:
        System() {}
        ~System() {
            for (auto it = _componentList.end(); it >= _componentList.begin(); it--) {
                delete *it;
            }
        }
        virtual void init() = 0;
        virtual void update(const float dt) = 0;

        void addComponent(Component* component) {
            _componentList.push_back(component);
        }
        void removeComponent(Component* component) {
            for (auto it = _componentList.begin(); it < _componentList.end(); it++) {
                if ((*it)->_UID == component->_UID) {
                    _componentList.erase(it);
                    return;
                }
            }
        }

    protected:
        std::vector<Component*> _componentList;
};

#endif
