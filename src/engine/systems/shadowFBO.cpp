#include "engine/systems/shadowFBO.hpp"

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <engine\window.hpp>

#include <iostream>

ShadowFBO::ShadowFBO(const uint32_t k_shadow_height, const uint32_t k_shadow_width, Shader* depthShader) : _depthShader(depthShader) {
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    glGenTextures(1, &_depthMap);
    glBindTexture(GL_TEXTURE_2D, _depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[]{ 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer Incomplete" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ShadowFBO::~ShadowFBO() {
    glDeleteFramebuffers(1, &_fbo);
    glDeleteTextures(1, &_depthMap);
}

uint32_t ShadowFBO::getFrameBuffer() const {
    return _fbo;
}
uint32_t ShadowFBO::getFrameTexture() const {
    return _depthMap;
}

void ShadowFBO::render() const {
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glViewport(0, 0, 1024, 1024);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void ShadowFBO::renderTexture(const Shader* shader) const {
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _depthMap);
    shader->set("depthMap", 2);
}

Shader* ShadowFBO::getShadowShader() const
{
    return _depthShader;
}
