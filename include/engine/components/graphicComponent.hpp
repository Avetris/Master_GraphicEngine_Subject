#ifndef __GRAPHIC_COMPONENT_H__
#define __GRAPHIC_COMPONENT_H__

#include <engine\components\component.hpp>
#include <engine\material.hpp>

class GraphicComponent : public Component {
    public:
        GraphicComponent(Handle* shader, uint16_t UID, Handle* gameObject);

        void init();
        void update(float dt);

        void setMaterial(Material* material);

        void setShader(Handle* shader);
        void setShader(Shader* shader);
        
        ~GraphicComponent();

        void setMaterial(Material* material);

    protected:
        Handle* _material = nullptr;
        Handle* _shader = nullptr;
};

#endif
