#include "engine/material.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>

Material::Material(const Texture& diffuse, const Texture& specular, const Texture& normal, int shininess) : _diffuse(diffuse), _specular(specular), _normal(normal), _shininess(shininess){
}

void Material::use(const Shader& shader, const bool useNormal) const {
    _diffuse.use(shader, "material.diffuse", 0);
    _specular.use(shader, "material.specular", 1);
    if(useNormal)
        _normal.use(shader, "material.normal", 2);
    shader.set("material.shininess", _shininess);
}