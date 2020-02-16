#ifndef __CAMERA_COMPONENT_H__
#define __CAMERA_COMPONENT_H__

#include <engine/components/Component.hpp>
#include <engine/shader.hpp>
#include <glm/glm.hpp>

const float k_Yaw = -90.0f;
const float k_Pitch = 0.0f;
const float k_Speed = 2.5f;
const float k_Sensitivity = 0.1f;
const float k_FOV = 45.0f;


const enum class InputMovement {
    Forward = 0,
    Backward = 1,
    Left = 2,
    Right = 3,
};

class CameraComponent : public Component{
    public:
        CameraComponent(uint16_t UID, GameObject* gameObject);
        void init();

        glm::mat4 getViewMatrix() const;
        glm::vec3 getCameraDirection() const;
        float getFOV() const;

        void handleKeyboard(InputMovement direction, float dt);
        void handleMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void handleMouseScroll(float yoffset);
        void renderCamera(Shader* shader) const;
        void reset();

    private:
        glm::vec3 _front, _up = glm::vec3(0.0f, 1.0f, 0.0f), _right, _worldUp = _up;
        glm::mat4 _viewMatrix;
        glm::mat4 _projection;
        float _yaw = k_Yaw, _pitch = k_Pitch;
        float _fov = k_FOV;
        void updateCameraVectors();
        void updateViewAndProjection();
};

#endif
