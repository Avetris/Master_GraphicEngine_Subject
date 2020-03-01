#include "engine/gpu.hpp"

void GPU::clearColor(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void GPU::clearBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GPU::enableCullFace()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void GPU::enableBlend() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GPU::bindGeometry(uint32_t& VAO, uint32_t* VBO, size_t nElements, size_t nVertex, const uint32_t* index, const float* positions, const float* uvs, const float* normals, const float* tangents, const float* biTangents)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(6, VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[0]);         //elements
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * nElements, index, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);                 //positions
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertex * 3, positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);                 //uvs
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertex * 2, uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);                 //normals
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertex * 3, normals, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);                 //tangents
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertex * 3, tangents, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);                 //bitangents
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertex * 3, biTangents, GL_STATIC_DRAW);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GPU::bindUIText(uint32_t& VAO, uint32_t* VBO, size_t nElements, size_t nVertex, const uint32_t* index, const float* positions, const float* uvs)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(3, VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[0]);         //elements
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * nElements, index, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);                 //positions
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertex * 2, positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);                 //uvs
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertex * 2, uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void GPU::deleteBuffers(uint16_t nBuffers, uint32_t VAO, uint32_t* VBO)
{
    glDeleteBuffers(nBuffers, VBO);
    glDeleteVertexArrays(1, &VAO);
}

void GPU::bindTexture(uint32_t& id, std::pair<GPU::Wrap, GPU::Wrap> wrap, std::pair<GPU::GPU::Filter, GPU::Filter> filter, std::pair<GPU::GPU::Filter, GPU::Filter> filterMipMap, Format format, int32_t width, int32_t height, unsigned char* data)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    GPU::applyWrapping(wrap);
    GPU::applyFilter(filter, filterMipMap);

    if (data) {

        glTexImage2D(GL_TEXTURE_2D, 0, format2GL(format), width, height, 0, format2GL(format), GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void GPU::applyWrapping(std::pair<GPU::Wrap, GPU::Wrap> wrap)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap2GL(wrap.first));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap2GL(wrap.second));
}

void GPU::applyFilter(std::pair<GPU::GPU::Filter, GPU::Filter> filter, std::pair<GPU::GPU::Filter, GPU::Filter> filterMipMap)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter2GL(filter.first, filterMipMap.first));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter2GL(filter.second, filterMipMap.second));
}

void GPU::useTexture(uint32_t id, uint32_t unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void GPU::deleteTexture(uint32_t id)
{
    glDeleteTextures(1, &id);
}

void GPU::changeViewPort(float width, float height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GPU::render(const uint32_t VAO, uint16_t nElements)
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, nElements, GL_UNSIGNED_INT, 0);
}

uint32_t GPU::wrap2GL(GPU::Wrap wrap)
{
    switch (wrap) {
    case GPU::Wrap::Repeat: return GL_REPEAT;
    case GPU::Wrap::Mirrored_Repeat: return GL_MIRRORED_REPEAT;
    case GPU::Wrap::Clamp_To_Border: return GL_CLAMP_TO_BORDER;
    case GPU::Wrap::Clamp_To_Edge: return GL_CLAMP_TO_EDGE;
    default: return GL_REPEAT;
    };
}

uint32_t GPU::filter2GL(GPU::Filter filter, GPU::Filter mipMap)
{
    switch (filter) {
        case GPU::Filter::Nearest: switch (mipMap) {
                case GPU::Filter::None: return GL_NEAREST;
                case GPU::Filter::Nearest: return GL_NEAREST_MIPMAP_NEAREST;
                case GPU::Filter::Linear: return GL_NEAREST_MIPMAP_LINEAR;
                default: return GL_NEAREST;
            };
        case GPU::Filter::Linear: switch (mipMap) {
            case GPU::Filter::None: return GL_LINEAR;
            case GPU::Filter::Nearest: return GL_LINEAR_MIPMAP_NEAREST;
            case GPU::Filter::Linear: return GL_LINEAR_MIPMAP_LINEAR;
            default: return GL_LINEAR;
        };
        case GPU::Filter::None:
        default: return GL_NEAREST;
    }
}

uint32_t GPU::format2GL(Format format)
{
    switch (format) {
    case GPU::Format::RGB: return GL_RGB;
    case GPU::Format::RGBA: return GL_RGBA;
    default:return GL_RGB;
    };
}


