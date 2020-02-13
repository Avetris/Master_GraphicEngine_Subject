#ifndef __CUBE_COMPONENT_H__
#define __CUBE_COMPONENT_H__ 1

#include "../renderComponent.hpp"

class CubeComponent final : public RenderComponent {
    public:
        CubeComponent() = delete;
        explicit CubeComponent(uint16_t UID, GameObject* gameObject, float size);

    private:
        float _size;
        void generateVertexData(float* positions, float* uvs, float* normals, uint32_t* indices, bool uvsDone) const;
};
#endif