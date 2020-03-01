#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1

#include <cstdint>
#include "component.hpp"
#include <engine\material.hpp>

//Attributes
//0 - positions
//1 - uvs
//2 - normals

class RenderComponent : public Component{
    public:
        RenderComponent(uint16_t UID, GameObject* gameObject, Shader* shader = nullptr);
        virtual ~RenderComponent();

        RenderComponent(const RenderComponent&) = default;
        RenderComponent& operator=(const RenderComponent&) = default;

        RenderComponent(RenderComponent&&) noexcept = default;
        RenderComponent& operator=(RenderComponent&&) noexcept = default;
        
        void setMaterial(Material* material);
        void setColor(glm::vec3 color);
        void setShader(Shader* shader);

        Shader* getShader() const;

        void setEnable(bool enable);

        virtual void init();
        void update(float dt);
        virtual void uploadToShader(bool renderColor, Shader* shader);

        virtual void render() const;

    protected:
        void uploadData(const float* positions, const float* uvs,
            const float* normals, const uint32_t* indices);

        void calcTangents(const float* positions, const float* uvs,
            const float* normals, float* tangents, float* biTangents) const;
    protected:
        uint32_t _VAO = 0;
        uint32_t _VBO[6] { 0,0,0,0,0,0 };
        uint32_t _nVertices = 0;
        uint32_t _nElements = 0;
        Material* _material = nullptr;
        Shader* _shader = nullptr;
        glm::vec3 _color = glm::vec3(0.5f, 0.5f, 0.5f);

};
#endif