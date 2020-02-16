#include "engine/material.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>

Material::Material(Texture* diffuse, Texture* specular, Texture* normal, int shininess) : _diffuse(diffuse), _specular(specular), _normal(normal), _shininess(shininess){
}
Material::Material(Texture* diffuse, Texture* specular, int shininess) : _diffuse(diffuse), _specular(specular), _shininess(shininess) {
}

bool Material::sameMaterial(Texture* diffuse, Texture* specular, Texture* normal, int shininess) const
{
    return _diffuse == diffuse && _specular == specular && _normal == normal && _shininess == shininess;
}

void Material::use(const Shader& shader) const {
    _diffuse->use(shader, "material.diffuse", 0);
    _specular->use(shader, "material.specular", 1);
    if(_normal != nullptr)
        _normal->use(shader, "material.normal", 2);
    shader.set("hasMaterial", true);
    shader.set("normalsEnabled", true);
    shader.set("material.shininess", _shininess);
}