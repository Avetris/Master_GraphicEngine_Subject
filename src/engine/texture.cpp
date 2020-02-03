#include "engine/texture.hpp"
#include "engine/shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>
#include <engine\gpu.hpp>

Texture::Texture(const char* path, GPU::Format format) : _format(format)
{
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path, &_width, &_height, &_depth, 0);
    
    if (data) {
        GPU::bindTexture(_id, _wrap, _filter, _filterMipMap, _format, _width, _height, data);
        stbi_image_free(data);
    }
    else {
        std::cout << "Failed to Load Texture " << path << std::endl;
    }
}

Texture::~Texture() {
    GPU::deleteTexture(_id);
}

void Texture::setWrap(GPU::Wrap s, GPU::Wrap t) {
    _wrap = std::make_pair(s, t);
    GPU::applyWrapping(_wrap);
}

void Texture::setFilter(GPU::Filter mag, GPU::Filter min, GPU::Filter mipMapMag, GPU::Filter mipMapMin) {
    _filter = std::make_pair(mag, min);
    _filterMipMap = std::make_pair(mipMapMag, mipMapMin);
    GPU::applyFilter(_filter, _filterMipMap);
}

void Texture::use(const Shader& shader, const char* name, uint32_t unit) const {
    GPU::useTexture(_id, unit);
    shader.set(name, static_cast<int32_t>(unit));
}