#ifndef __QUAD_COMPONENT_H__
#define __QUAD_COMPONENT_H__ 1

#include "../renderComponent.hpp"

class QuadComponent final: public RenderComponent {
    public:
        QuadComponent() = delete;
        explicit QuadComponent(uint16_t UID, GameObject* gameObject, float size);

    private:
        float _size;
};
#endif