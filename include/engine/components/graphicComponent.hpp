#ifndef __GRAPHIC_COMPONENT_H__
#define __GRAPHIC_COMPONENT_H__

#include <engine\components\component.hpp>
#include <engine\material.hpp>

class GraphicComponent : public Component {
    public:
        GraphicComponent(uint16_t UID, GameObject* gameObject);

        void init();
        void update(float dt);

        void setMaterial(Material* material);

        void setShader(Shader* shader);
        
        ~GraphicComponent();

    protected:
        Material* _material = nullptr;
        Shader* _shader = nullptr;
};

#endif
