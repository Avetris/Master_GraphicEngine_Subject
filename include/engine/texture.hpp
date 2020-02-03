#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <cstdint>
#include <string>
#include <engine\gpu.hpp>

class Shader;

class Texture {
    public:
        Texture(const char* path, GPU::Format format);
        Texture() = delete;
        ~Texture();

        Texture(const Texture&) = default;
        Texture(Texture&&) = default;
        Texture& operator=(const Texture&) = default;
        Texture& operator=(Texture&&) = default;

        void use(const Shader& shader, const char* name, uint32_t unit = 0) const;

        void setWrap(GPU::Wrap s, GPU::Wrap t);
        void setFilter(GPU::Filter mag, GPU::Filter min, GPU::Filter mipMapMag = GPU::Filter::None, GPU::Filter mipMapMin = GPU::Filter::None);

    private:
        uint32_t _id = 0;
        GPU::Format _format = GPU::Format::RGB;
        int32_t _width = 0, _height = 0;
        int32_t _depth = 0;
        std::pair<GPU::Wrap, GPU::Wrap>_wrap{ GPU::Wrap::Repeat, GPU::GPU::Wrap::Repeat };
        std::pair<GPU::GPU::Filter, GPU::Filter>_filter{ GPU::Filter::Linear, GPU::Filter::Linear };
        std::pair<GPU::GPU::Filter, GPU::Filter>_filterMipMap{ GPU::Filter::None, GPU::Filter::None };
};

#endif