#include "engine/material.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>


Material::Material(const Texture& diffuse, const Texture& specular, int shininess) : _diffuse(diffuse), _specular(specular), _shininess(shininess){
}

void Material::use(const Shader& shader) const {
    _diffuse.use(shader, "material.diffuse", 0);
    _specular.use(shader, "material.specular", 1);
    shader.set("material.shininess", _shininess);
}