#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <engine/components/Component.hpp>
#include <glm/glm.hpp>

const float k_Yaw = -90.0f;
const float k_Pitch = 0.0f;
const float k_Speed = 2.5f;
const float k_Sensitivity = 0.1f;
const float k_FOV = 45.0f;

class CameraComponent : public Component{
    public:
        enum class Movement {
            Forward = 0,
            Backward = 1,
            Left = 2,
            Right = 3,
        };

        CameraComponent(uint16_t UID, Handle* gameObject);
        void init();
        void update(float dt);
        ~CameraComponent();

        glm::mat4 getViewMatrix() const;
        glm::vec3 getCameraDirection() const;
        float getFOV() const;

        void handleKeyboard(Movement direction, float dt);
        void handleMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void handleMouseScroll(float yoffset);

    private:
        glm::vec3 _front, _up = glm::vec3(0.0f, 1.0f, 0.0f), _right, _worldUp;
        float _yaw = k_Yaw, _pitch = k_Pitch;
        float _fov;
        void updateCameraVectors();
};

#endif
