#ifndef __SPHERE_COMPONENT_H__
#define __SPHERE_COMPONENT_H__ 1

#include "../renderComponent.hpp"
#include <vector>

class SphereComponent final : public RenderComponent {
    public:
        SphereComponent() = delete;
        SphereComponent(uint16_t UID, GameObject* gameObject, float radius, uint32_t stacks, uint32_t slices);

    private:
        void generateVertexData(float* positions, float* uvs, float* normals, uint32_t* indices) const;

    private:
        float _radius;
        uint32_t _stacks, _slices;
};

#endif