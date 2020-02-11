#ifndef __CUBE_H__
#define __CUBE_H__ 1

#include "../geometryComponent.hpp"

class Cube final : public GeometryComponent {
    public:
        Cube() = delete;
        explicit Cube(float size);
        explicit Cube(float size, float *uvs);

    private:
        float _size;
        void generateVertexData(float* positions, float* uvs, float* normals, uint32_t* indices, bool uvsDone) const;
};
#endif