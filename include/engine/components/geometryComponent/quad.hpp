#ifndef __QUAD_H__
#define __QUAD_H__ 1

#include "../geometryComponent.hpp"

class Quad final: public GeometryComponent {
    public:
        Quad() = delete;
        explicit Quad(float size);

    private:
        float _size;
};
#endif