#ifndef __SHADOW_FBO_H__
#define __SHADOW_FBO_H__ 1

#include <cstdint>
#include <engine\shader.hpp>

class ShadowFBO {
    public:
        ShadowFBO(const uint32_t k_shadow_height, const uint32_t k_shadow_width, Shader* depthShader);
        ~ShadowFBO();

        ShadowFBO(const ShadowFBO&) = default;
        ShadowFBO& operator=(const ShadowFBO&) = default;

        ShadowFBO(ShadowFBO&&) noexcept = default;
        ShadowFBO& operator=(ShadowFBO&&) noexcept = default;

        uint32_t getFrameBuffer() const;
        uint32_t getFrameTexture() const;

        void render() const;
        void renderTexture(const Shader* shader) const;
        void use(const Shader* shader) const;

        Shader* getShadowShader() const;

    protected:
        uint32_t _fbo = 0;
        uint32_t _depthMap = 0;
        Shader* _depthShader;

};
#endif