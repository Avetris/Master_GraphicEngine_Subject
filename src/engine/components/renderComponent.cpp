#include <engine/components/renderComponent.hpp>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <engine/gpu.hpp>
#include <engine\engine.hpp>
#include <engine\systems\renderSystem.hpp>
#include <engine\gameObject.hpp>

RenderComponent::RenderComponent(uint16_t UID, GameObject* gameObject, Shader* shader) : Component(UID, gameObject) {
    if (!shader) {
        _shader = Engine::instance()->getSystem<RenderSystem>()->getShader(GenericShaderType::BLINN);
    }
    else {
        _shader = shader;
    }
}

RenderComponent::~RenderComponent() {
    GPU::deleteBuffers(4, _VAO, _VBO);
}

void RenderComponent::calcTangents(const float* positions, const float* uvs, const float* normals, float* tangents, float* biTangents) const {
    for (size_t i = 0; i < _nVertices; i += 3) {
        const uint32_t idx3 = i * 3;
        const uint32_t idx2 = i * 2;

        glm::vec3 v0(positions[idx3 + 0], positions[idx3 + 1], positions[idx3 + 2]);
        glm::vec3 v1(positions[idx3 + 3], positions[idx3 + 4], positions[idx3 + 5]);
        glm::vec3 v2(positions[idx3 + 6], positions[idx3 + 7], positions[idx3 + 8]);

        glm::vec2 uv0(uvs[idx2 + 0], uvs[idx2 + 1]);
        glm::vec2 uv1(uvs[idx2 + 2], uvs[idx2 + 3]);
        glm::vec2 uv2(uvs[idx2 + 4], uvs[idx2 + 5]);

        glm::vec3 deltaPos1 = v1 - v0;
        glm::vec3 deltaPos2 = v2 - v0;

        glm::vec2 deltaUv1 = uv1 - uv0;
        glm::vec2 deltaUv2 = uv2 - uv0;

        float r = 1 / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * r;
        glm::vec3 biTangent = (deltaPos2 * deltaUv1.x - deltaPos1 * deltaUv2.x) * r;

        tangents[idx3 + 0] = tangents[idx3 + 3] = tangents[idx3 + 6] = tangent.x;
        tangents[idx3 + 1] = tangents[idx3 + 4] = tangents[idx3 + 7] = tangent.y;
        tangents[idx3 + 2] = tangents[idx3 + 5] = tangents[idx3 + 8] = tangent.z;

        biTangents[idx3 + 0] = biTangents[idx3 + 3] = biTangents[idx3 + 6] = biTangent.x;
        biTangents[idx3 + 1] = biTangents[idx3 + 4] = biTangents[idx3 + 7] = biTangent.y;
        biTangents[idx3 + 2] = biTangents[idx3 + 5] = biTangents[idx3 + 8] = biTangent.z;
    }

    for (size_t i = 0; i < _nVertices; ++i) {
        const uint32_t idx3 = i * 3;

        glm::vec3 n(normals[idx3 + 0], normals[idx3 + 1], normals[idx3 + 2]);
        glm::vec3 t(tangents[idx3 + 0], tangents[idx3 + 1], tangents[idx3 + 2]);
        glm::vec3 b(biTangents[idx3 + 0], biTangents[idx3 + 1], biTangents[idx3 + 2]);

        t = glm::normalize(t - n * glm::dot(t, n));

        if (glm::dot(glm::cross(n, t),b) < 0.0f) {
            t = t * -1.0f;
        }

        tangents[idx3 + 0] = t.x;
        tangents[idx3 + 1] = t.y;
        tangents[idx3 + 2] = t.z;
    }
}

void RenderComponent::uploadData(const float* positions, const float* uvs, const float* normals,
    const uint32_t* indices) {
    const size_t length = _nVertices * 3;
    const auto tangents = new float[length];
    const auto biTangents = new float[length];

    // TODO improve tangents getter for sphere
    if (dynamic_cast<SphereComponent*>(this)) {
        memset(tangents, 0.0f, length * sizeof(float));
        memset(biTangents, 0.0f, length * sizeof(float));
    }
    else {
        calcTangents(positions, uvs, normals, tangents, biTangents);
    }

    GPU::bindGeometry(_VAO, _VBO, _nElements, _nVertices, indices, positions, uvs, normals, tangents, biTangents);

    delete[] tangents;
    delete[] biTangents;
}

void RenderComponent::setMaterial(Material* material)
{
    _material = material;
}

void RenderComponent::setColor(glm::vec3 color) {
    _color = color;
}

void RenderComponent::setShader(Shader* shader)
{
    _shader = shader;
    Engine::instance()->getSystem<RenderSystem>()->setReloadShaders();
}

Shader* RenderComponent::getShader() const {
    return _shader;
}

void RenderComponent::init()
{
}

void RenderComponent::update(float dt)
{
    _shader->use();
    uploadToShader(true, _shader);
}

void RenderComponent::uploadToShader(bool renderColor, Shader* shader)
{
    if (renderColor) {
        if (_material != nullptr) {
            _material->use(*shader);
        }
        else
        {
            shader->set("hasMaterial", false);
            shader->set("modelColor", _color);
            shader->set("normalsEnabled", false);
        }
    }
    TransformComponent* transformComponent = _gameObject->getComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
    if (transformComponent != nullptr)
        transformComponent->renderMatrix(shader);
    ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(this);
    if (modelComponent) {
        shader->set("hasMaterial", true);
        shader->set("normalsEnabled", true);
        modelComponent->render(shader);
    }else{
        render();
    }
}

void RenderComponent::render() const {
    GPU::render(_VAO, _nElements);
}

void RenderComponent::setEnable(bool enable) {
    Component::setEnable(enable);
    Engine::instance()->getSystem<RenderSystem>()->setReloadShaders();
}