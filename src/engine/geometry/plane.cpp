#include "engine/geometry/plane.hpp"

Plane::Plane(float width, float depth) : _width(width), _depth(depth){
    _nVertices = 1 * 2 * 3;  //1 face * 2 triangles * 3 vertices
    _nElements = _nVertices;

    float x = width / 2;
    float z = depth/ 2;

    float positions[] = { x, 0.0f, z,    //upper right triangle
                          x, 0.0f, -z,
                          -x, 0.0f, z,
                          -x, 0.0f, -z};

    float uvs[] = { 1.0f, 1.0f,
                    0.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f };

    float normals[] = { 0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f };

    uint32_t indices[] = { 0, 1, 2,
                           2 , 1, 3 };

    uploadData(positions, uvs, normals, indices);
}