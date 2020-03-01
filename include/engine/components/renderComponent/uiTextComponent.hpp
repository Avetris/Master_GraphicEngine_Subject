#ifndef __UI_TEXT_COMPONENT_H__
#define __UI_TEXT_COMPONENT_H__ 1

#include "../renderComponent.hpp"
#include <engine/texture.hpp>
#include <string>
#include <vector>
#include <map>


class UITextComponent : public RenderComponent {
    public:
        UITextComponent() = delete;
        explicit UITextComponent(uint16_t UID, GameObject* gameObject, Shader* shader);

        void getCharacters();

        void makeText();

        void uploadToShader(bool renderColor, Shader* shader) override;

        void setFont(char* fontLocation, std::string availableChars);
        void setText(std::string text, bool wrapping = true);
        void setPositon(glm::vec2 position);
        void setFontSize(float size);


    private:
        std::map<char, std::vector<float>> _characters;
        Texture* _texture;
        bool _wrapping = true;
        glm::vec2 _position = glm::vec2(-1.0f, 1.0f);
        float _fontSize = 0.05f;
        std::string _text;
        std::vector<std::string> _availableChars;
};
#endif