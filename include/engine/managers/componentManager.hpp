#ifndef __COMPONENT_MANAGER_H__
#define __COMPONENT_MANAGER_H__

#include <cstdint>
#include <glm/glm.hpp>
#include <engine\components\component.hpp>

const size_t NUMBER_COMPONENTS = 1;
const enum TYPE {
    NON_COMPONENT = -1,
    INPUT_COMPONENT = 0,
    TRANSFORM_COMPONENT = 1,
    PHYSIC_COMPONENT = 2,
    LOGIC_COMPONENT = 3,
    CAMERA_COMPONENT = 4,
    GRAPHIC_COMPONENT = 5,
    UI_COMPONENT = 6,
    AUDIO_COMPONENT = 7
};

class ComponentManager{
    public:
        static ComponentManager* instance() {
            static ComponentManager i;
            return &i;
        }

        Component* createComponent(Handle* gameObject, TYPE componentType);


    private:
        ComponentManager();
        static uint16_t _GUID;
};
#endif
