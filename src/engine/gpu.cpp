#include "engine/gpu.hpp"

#include <glm/gtc/matrix_transform.hpp>

template <class T>
static Vector3<T> GPU::normalize(const Vector3<T>& vec) {
    return glm::normalize(vec);
}

template <class T>
static Vector3<T> GPU::cross(const Vector3<T>& vec1, const Vector3<T>& vec2) {
    return glm::cross(vec1, vec2);
}
template <class T>
static glm::mat4 GPU::lookAt(const Vector3<T>& position, const Vector3<T>& direction, const Vector3<T>& up) {
    return glm::lookAt(position, direction, up);
}

