#include "engine/material.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>


Material::Material(const Texture& albedo, const Texture& specular, int shininess) : _albedo(albedo), _specular(specular), _shininess(shininess){
}

void Material::use(const Shader& shader) const {
    _albedo.use(shader, "material.diffuse", 0);
    _specular.use(shader, "material.specular", 1);
    shader.set("material.shininess", _shininess);
}