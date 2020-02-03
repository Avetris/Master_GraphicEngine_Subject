#ifndef __GPU_H__
#define __GPU_H__
#include <glm/glm.hpp>
#include <string>

class GPU {
    public:
        enum class Wrap {
            Repeat,
            Mirrored_Repeat,
            Clamp_To_Border,
            Clamp_To_Edge
        };

        enum class Filter {
            None,
            Nearest,
            Linear
        };

        enum class Format {
            RGB,
            RGBA
        };
        static void enableCullFace();

        // Geometry
        static void bindGeometry(uint32_t& VAO, uint32_t* VBO, size_t nElements, size_t nVertex, const uint32_t* index, const float* positions, const float* uvs, const float* normals, const float* tangents, const float* biTangents);

        static void deleteBuffers(uint16_t nBuffers, uint32_t VAO, uint32_t* VBO);

        static void render(const uint32_t VAO, uint16_t nElements);

        // Textures
        static void bindTexture(uint32_t& id, std::pair<GPU::Wrap, GPU::Wrap>_wrap, std::pair<GPU::GPU::Filter, GPU::Filter>_filter, std::pair<GPU::GPU::Filter, GPU::Filter>_filterMipMap, Format format, int32_t width, int32_t height, unsigned char* data);
        static void applyWrapping(std::pair<GPU::Wrap, GPU::Wrap> wrap);
        static void applyFilter(std::pair<GPU::GPU::Filter, GPU::Filter> filter, std::pair<GPU::GPU::Filter, GPU::Filter> filterMipMap);
        static void useTexture(uint32_t id, uint32_t unit);
        static void deleteTexture(uint32_t id);

    private:
        static uint32_t wrap2GL(Wrap wrap);
        static uint32_t filter2GL(GPU::Filter filter, GPU::Filter mipMap);
        static uint32_t format2GL(Format format);
};

#endif
