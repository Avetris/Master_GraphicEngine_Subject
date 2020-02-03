#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <glm/glm.hpp>
#include <engine/gpu.hpp>

const float k_Yaw = -90.0f;
const float k_Pitch = 0.0f;
const float k_Speed = 2.5f;
const float k_Sensitivity = 0.1f;
const float k_FOV = 45.0f;

class Camera {
    public:
        enum class Movement {
            Forward = 0,
            Backward = 1,
            Left = 2,
            Right = 3,
        };
        Camera(const Vector3<float> position, const Vector3<float> up, float yaw, float pitch);
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        glm::mat4 getViewMatrix() const;
        Vector3<float> getCameraDirection() const;
        float getFOV() const;
        Vector3<float> getPosition() const;

        void handleKeyboard(Movement direction, float dt, bool canFly = true);
        void handleMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void handleMouseScroll(float yoffset);

    private:
        Vector3<float> _position, _front, _up, _right, _worldUp;
        float _yaw, _pitch;
        float _fov;
        void updateCameraVectors();
};

#endif
