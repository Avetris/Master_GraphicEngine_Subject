#ifndef __FBO_H__
#define __FBO_H__ 1

#include <cstdint>
#include <engine\shader.hpp>

class FBO {
    public:
        FBO();
        ~FBO();

        FBO(const FBO&) = default;
        FBO& operator=(const FBO&) = default;

        FBO(FBO&&) noexcept = default;
        FBO& operator=(FBO&&) noexcept = default;

        void render() const;
        void renderTexture(const Shader& shader) const;

    protected:
        uint32_t _fbo = 0;
        uint32_t _textureColor = 0;
        uint32_t _rbo = 0;

};
#endif