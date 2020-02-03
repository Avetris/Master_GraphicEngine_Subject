#ifndef __GPU_MODELS_H__
#define __GPU_MODELS_H__

#include <glm/glm.hpp>

template <class T>
struct Vector3
{
    float x, y, z;
    Vector3();
    Vector3(T x, T y, T z);
    operator glm::vec3() const;
    Vector3<T> operator+ (Vector3<T> vector3) const;
    Vector3<T> operator* (T value) const;
};
#endif
