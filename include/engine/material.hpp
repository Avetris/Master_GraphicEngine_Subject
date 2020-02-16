#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <cstdint>
#include <string>
#include "texture.hpp"
#include <memory>

class Shader;

class Material {
    public:
        Material(Texture* diffuse, Texture* specular, Texture* normal, int shininess);
        Material(Texture* diffuse, Texture* specular, int shininess);
        Material() = delete;

        Material(const Material&) = default;
        Material(Material&&) = default;
        Material& operator=(const Material&) = default;
        Material& operator=(Material&&) = default;

        bool sameMaterial(Texture* diffuse, Texture* specular, Texture* normal, int shininess) const;
        void use(const Shader& shader) const;
        
    private:
        Texture* _diffuse;
        Texture* _specular;
        Texture* _normal = nullptr;
        int _shininess;
};

#endif