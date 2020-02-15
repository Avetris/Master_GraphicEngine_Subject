#define _USE_MATH_DEFINES

#include <engine/components/renderComponent/cubeComponent.hpp>

#include <cmath>

CubeComponent::CubeComponent(uint16_t UID, GameObject* gameObject, float size) : RenderComponent(UID, gameObject), _size(size) {
    _nVertices = 6 * 4;   //6 faces * 4 vertices;
    _nElements = 6 * 2 * 3; // 6 faces * 2 triangles * 3 vertices

    const auto positions = new float[static_cast<size_t>(_nVertices) * 3];
    const auto uvs = new float[static_cast<size_t>(_nVertices) * 2];
    const auto normals = new float[static_cast<size_t>(_nVertices) * 3]{ 0.0f };

    const auto indices = new uint32_t[_nElements];
    generateVertexData(positions, uvs, normals, indices, false);

    uploadData(positions, uvs, normals, indices);

    delete[] positions;
    delete[] uvs;
    delete[] normals;
    delete[] indices;
}

void CubeComponent::generateVertexData(float* positions, float* uvs, float* normals, uint32_t* indices, bool uvsDone) const {
    const auto half = _size / 2; 
    const auto radius = sqrt(3 * pow(half, 2)); // radius with the formula sqrt(x^2 + y^2 + z^2)

    const auto thetaFac = acosf(half / radius); // initial theta grade with formula acos(z / radius)
    const auto phiFac = atanf(half / half); // initial phi grade with formula atan(x / y)

    uint32_t idx = 0, tIdx = 0;
    int32_t pos[8][3] = { // It is setted the position of each vertex here so the index array can be created easier.
        {21,15,0},
        {-16,14,1},
        {-19,-5,2},
        {22,-4,3},
        {-18,-6,-9},
        {23,-7,-8},
        {20,12,-11},
        {-17 ,13,-10}
    };
    // Generate positions and normals
    for (size_t i = 0; i < 2; i++) {
        const float theta = thetaFac + (i * M_PI);
        for (size_t j = 0; j < 4; j++) {
            const float phi = phiFac + (j * M_PI / 2);
            const float nx = sin(theta) * cos(phi);
            const float ny = sin(theta) * sin(phi);
            const float nz = cos(theta);
            for (size_t k = 0; k < 3; k++) {
                tIdx = abs(pos[idx][k]) * 3;
                positions[tIdx] = radius * nx; 
                positions[tIdx + 1] = radius * ny; 
                positions[tIdx + 2] = radius * nz;
                int32_t n = 1;
                if (pos[idx][k] < 0) {
                    n = -1;
                }
                normals[tIdx + k] = n;
            }
            idx ++;
        }
    }

    idx = 0;
    tIdx = 0;             
    // Generate the element list and the uvs
    for (size_t i = 0; idx < _nElements; i += 4) {
        indices[idx] = i;
        indices[idx + 1] = i + 1;
        indices[idx + 2] = i + 2;

        indices[idx + 3] = i;
        indices[idx + 4] = i + 2;
        indices[idx + 5] = i + 3;
        idx += 6;
        
        if (!uvsDone) {
            uvs[tIdx] = 1.0f;
            uvs[tIdx + 1] = 0.0f;

            uvs[tIdx + 2] = 0.0f;
            uvs[tIdx + 3] = 0.0f;

            uvs[tIdx + 4] = 0.0f;
            uvs[tIdx + 5] = 1.0f;

            uvs[tIdx + 6] = 1.0f;
            uvs[tIdx + 7] = 1.0f;
            tIdx += 8;
        }
    }
}