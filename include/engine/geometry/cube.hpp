#ifndef __CUBE_H__
#define __CUBE_H__ 1

#include "geometry.hpp"

class Cube final : public Geometry {
    public:
        Cube() = delete;
        explicit Cube(float size);
        explicit Cube(float size, float *uvs);

    private:
        float _size;
        void generateVertexData(float* positions, float* uvs, float* normals, uint32_t* indices, bool uvsDone) const;
};
#endif