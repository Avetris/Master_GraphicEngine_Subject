#ifndef __GPU_H__
#define __GPU_H__

#include <glm/glm.hpp>
#include <engine/gpuModels.hpp>


class GPU {
    public:
        template <class T>
        static Vector3<T> normalize(const Vector3<T>& vec);

        template <class T>
        static Vector3<T> cross(const Vector3<T>& vec1, const Vector3<T>& vec2);

        template <class T>
        static glm::mat4 lookAt(const Vector3<T>& position, const Vector3<T>& direction, const Vector3<T>& up);
};

#endif
