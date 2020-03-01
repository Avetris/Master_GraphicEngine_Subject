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
        void setText(std::string text);


    private:
        std::map<char, std::vector<float>> _characters;
        Texture* _texture;
        std::string _text;
        std::vector<std::string> _availableChars;
};
#endif