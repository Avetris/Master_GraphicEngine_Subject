#ifndef __CAMERA_INPUT_COMPONENT_H__
#define __CAMERA_INPUT_COMPONENT_H__

#include <engine\components\inputComponent.hpp>
#include <engine\components\cameraComponent.hpp>

class CameraInputComponent : public InputComponent {
public:
    CameraInputComponent(uint16_t UID, GameObject* gameObject);
    
    void onKeyPressed(GPU::KeyId key, GPU::KeyActions action) override;
    void onMouseMoved(float x, float y) override;
    void onScrollMoved(float x, float y) override;
    
    void init() override;
    void update(float dt) override;

    void setEnable(bool enable);

    private:
        float lastX = 0.0f, lastY = 0.0f;
        bool firstMouse = true;
        CameraComponent* _camera = nullptr;
};

#endif