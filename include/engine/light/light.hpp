#ifndef __LIGHT_H__
#define __LIGHT_H__ 1

#include <glm/glm.hpp>
#include <cstdint>
#include <string>


class Shader;

class Light {
    public:
        Light(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

        Light(const Light&) = default;
        Light& operator=(const Light&) = default;

        Light(Light&&) noexcept = default;
        Light& operator=(Light&&) noexcept = default;

        void setName(std::string name);
        void setPosition(glm::vec3 position);
        glm::vec3 getPosition() const;
        void setColor(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular);
        glm::vec3 getSpecular() const;

        virtual void use(const Shader& shader) const;
        //void render(glm::mat4 view, glm::mat4 proj) const;
        
    protected:
        std::string _name = "";
        glm::vec3 _position = glm::vec3(0.0f);
        glm::vec3 _color = glm::vec3(0.0f);
        glm::vec3 _ambient = glm::vec3(0.0f);
        glm::vec3 _diffuse = glm::vec3(0.0f);
        glm::vec3 _specular = glm::vec3(0.0f);
};

#endif