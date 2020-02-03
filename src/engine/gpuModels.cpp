#include "engine/gpuModels.hpp"

template<class T>
Vector3<T>::Vector3(): x(0.0f), y(0.0f), z(0.0f) {}

template<class T>
Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z){}

template <class T>
Vector3<T>::operator glm::vec3() const
{
    glm::vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

template<class T>
Vector3<T> Vector3<T>::operator+ (Vector3<T> vector3) const
{
    x += vector3.x;
    y += vector3.y;
    z += vector3.z;
    return *this;
}

template<class T>
Vector3<T> Vector3<T>::operator* (T value) const
{
    x *= value;
    y *= value;
    z *= value;
    return *this;
}