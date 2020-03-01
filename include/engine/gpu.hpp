#ifndef __GPU_H__
#define __GPU_H__
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class GPU {
    public:
        enum class KeyId {
            A = GLFW_KEY_A,
            B = GLFW_KEY_B,
            C = GLFW_KEY_C,
            D = GLFW_KEY_D,
            E = GLFW_KEY_E,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            I = GLFW_KEY_I,
            J = GLFW_KEY_J,
            K = GLFW_KEY_J,
            L = GLFW_KEY_L,
            M = GLFW_KEY_M,
            N = GLFW_KEY_N,
            O = GLFW_KEY_O,
            P = GLFW_KEY_P,
            Q = GLFW_KEY_Q,
            R = GLFW_KEY_R,
            S = GLFW_KEY_S,
            T = GLFW_KEY_T,
            U = GLFW_KEY_U,
            V = GLFW_KEY_V,
            W = GLFW_KEY_W,
            X = GLFW_KEY_X,
            Y = GLFW_KEY_Y,
            Z = GLFW_KEY_Z,
            UP = GLFW_KEY_UP,
            DOWN = GLFW_KEY_DOWN,
            LEFT = GLFW_KEY_LEFT,
            RIGHT = GLFW_KEY_RIGHT,
            SPACE = GLFW_KEY_SPACE,
            ESCAPE = GLFW_KEY_ESCAPE,
            LEFT_SHIFT =  GLFW_KEY_LEFT_SHIFT,
            LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
            LEFT_ALT = GLFW_KEY_LEFT_ALT,
            LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
            RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
            RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
            RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
            RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
            MENU = GLFW_KEY_MENU
        };
        
        enum class KeyActions {
            RELEASE = GLFW_RELEASE,
            PRESS = GLFW_PRESS,
            REPEAT = GLFW_REPEAT
        };

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

        static void clearBuffer();
        static void clearColor(float red, float green, float blue, float alpha);
        static void enableCullFace();
        static void enableBlend();

        // Geometry
        static void bindGeometry(uint32_t& VAO, uint32_t* VBO, size_t nElements, size_t nVertex, const uint32_t* index, const float* positions, const float* uvs, const float* normals, const float* tangents, const float* biTangents);

        static void bindUIText(uint32_t& VAO, uint32_t* VBO, size_t nElements, size_t nVertex, const uint32_t* index, const float* positions, const float* uvs);

        static void deleteBuffers(uint16_t nBuffers, uint32_t VAO, uint32_t* VBO);

        static void render(const uint32_t VAO, uint16_t nElements);

        // Textures
        static void bindTexture(uint32_t& id, std::pair<GPU::Wrap, GPU::Wrap>_wrap, std::pair<GPU::GPU::Filter, GPU::Filter>_filter, std::pair<GPU::GPU::Filter, GPU::Filter>_filterMipMap, Format format, int32_t width, int32_t height, unsigned char* data);
        static void applyWrapping(std::pair<GPU::Wrap, GPU::Wrap> wrap);
        static void applyFilter(std::pair<GPU::GPU::Filter, GPU::Filter> filter, std::pair<GPU::GPU::Filter, GPU::Filter> filterMipMap);
        static void useTexture(uint32_t id, uint32_t unit);
        static void deleteTexture(uint32_t id);
        static void changeViewPort(float width, float height);

    private:
        static uint32_t wrap2GL(Wrap wrap);
        static uint32_t filter2GL(GPU::Filter filter, GPU::Filter mipMap);
        static uint32_t format2GL(Format format);
};

#endif
