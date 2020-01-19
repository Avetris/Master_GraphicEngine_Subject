#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <cstdint>
#include <string>
#include "texture.hpp"

class Shader;

class Material {
    public:
        Material(const Texture& diffuse, const Texture& specular, const Texture& normal, int shininess);
        Material() = delete;

        Material(const Material&) = default;
        Material(Material&&) = default;
        Material& operator=(const Material&) = default;
        Material& operator=(Material&&) = default;

        void use(const Shader& shader, const bool useNormal = false) const;
        
    private:
        Texture _diffuse;
        Texture _specular;
        Texture _normal;
        int _shininess;
};

#endif