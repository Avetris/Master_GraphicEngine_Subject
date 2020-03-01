#include <engine/components/renderComponent/uiTextComponent.hpp>
#include <engine/shader.hpp>
#include <engine/gameObject.hpp>
#include <iostream>

UITextComponent::UITextComponent(uint16_t UID, GameObject* gameObject, Shader* shader) : RenderComponent(UID, gameObject, shader) {
    _texture = new Texture("../assets/fonts/game_font.png", GPU::Format::RGBA);
    _availableChars.push_back("ABCDEFGHI");
    _availableChars.push_back("JKLMNOPQR");
    _availableChars.push_back("STUVWXYZ ");
    _availableChars.push_back("abcdefghi");
    _availableChars.push_back("jklmnopqr");
    _availableChars.push_back("stuvwxyz");
    _availableChars.push_back("012345678");
    _availableChars.push_back("9.,;:$#'!");
    _availableChars.push_back("\"/?%&()@");
    getCharacters();
}

void UITextComponent::getCharacters()
{
    // Load first 128 characters of ASCII set
    size_t i = 0, j = 0;
    for (std::string line : _availableChars)
    {
        i = 0;
        for (char c : line)
        {
            std::vector<float> uvs{
                  0.11f * (i + 1), 1.0f - (0.1f * j),
                  0.11f * (i + 1), 0.91f - (0.111f * j),
                  0.111f * i, 1.0f - (0.1f * j),
                  0.111f * i, 0.91f - (0.111f * j)
            };
            _characters.insert({ c, uvs });
            i++;
        }
        j++;
    }
    makeText();
}

void UITextComponent::makeText()
{
    float size = 0.1f;
    float pos = 0.0f;
    int i = 0;
    size_t nVertexIteration = 1 * 4;
    size_t nVertex = nVertexIteration * _text.size();
    _nElements = 1 * 2 * 3 *  _text.size();

    uint32_t index[] = { 0, 2, 1,
                        2, 3, 1};
    float positions[] = { size, size,
                          size , -size,
                          -size, size,
                          -size, -size };

    uint32_t* indexGlobal = new uint32_t[_nElements];
    float* positionsGlobal = new float[nVertex * 2];
    float* uvsGlobal = new float[nVertex * 2];
    for (char c : _text)
    {
        auto itr = _characters.find(c);
        if (itr != _characters.end()) {
            std::vector<float> uvs = itr->second;
            for (size_t k = 0; k < (nVertexIteration * 2); k++) {
                positionsGlobal[(i * nVertexIteration * 2) + k] = positions[k] + (k % 2 == 0 ? pos : 0.0f);
                uvsGlobal[(i * nVertexIteration * 2) + k] = uvs[k];
                if (k < 6) {                    
                    indexGlobal[(i * 6) + k] = index[k] + (i * 4);
                }
            }

            pos += (size * 2);
            i++;
        }
    }
    GPU::bindUIText(_VAO, _VBO, _nElements, nVertex, indexGlobal, positionsGlobal, uvsGlobal);
}

void UITextComponent::uploadToShader(bool renderColor, Shader* shader)
{
    if (renderColor) {
        shader->set("textColor", _color);

        if (_texture) {
            _texture->use(*shader, "textTexture", 0);
        }
        render();
        TransformComponent* transformComponent = _gameObject->getComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
        if (transformComponent != nullptr)
            transformComponent->renderMatrix(shader);
    }
}

void UITextComponent::setFont(char* fontLocation, std::string availableChars)
{
    if (_texture) {
        delete _texture;
    }
    _texture = new Texture(fontLocation, GPU::Format::RGBA);
    _characters.clear();
    getCharacters();
}

void UITextComponent::setText(std::string text)
{
    _text = text;
    makeText();
}
