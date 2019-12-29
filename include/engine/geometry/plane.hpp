#ifndef __PLANE_H__
#define __PLANE_H__ 1

#include "geometry.hpp"

class Plane final: public Geometry {
    public:
        Plane() = delete;
        explicit Plane(float width, float depth);

    private:
        float _width;
        float _depth;
};
#endif