#include "engine/components/transformComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <engine\systems\transformSystem.hpp>
#include <engine\engine.hpp>
#include <engine\gameObject.hpp>


TransformComponent::TransformComponent(uint16_t UID, GameObject* gameObject) :Component(UID, gameObject) {}

void TransformComponent::init()
{
}

void TransformComponent::update(float dt)
{
	if (modelNeedsToUpdate()) {
		updateModel(glm::mat4(1.0f));
	}
}

TransformComponent::~TransformComponent()
{
	_gameObject->removeComponent(ComponentType::TRANSFORM_COMPONENT);
	Engine::instance()->getSystem<TransformSystem>()->removeComponent(static_cast<Component*>(this));
}

void TransformComponent::move(glm::vec3 direction, bool add)
{
	if (add) {
		_gameObject->setPosition(_gameObject->getPosition() + direction);
	}
	else {
		_gameObject->setPosition(direction);
	}
	_modelToUpdate = true;
}

void TransformComponent::scale(glm::vec3 scale, bool add)
{
	if (add) {
		_gameObject->setScale(_gameObject->getScale() + scale);
	}
	else {
		_gameObject->setScale(scale);
	}
	_modelToUpdate = true;
}

void TransformComponent::rotate(float angle, glm::vec3 axis, bool add)
{
	if (add) {
		// TODO --> This is incorrect!
		_gameObject->setRotation(angle + angle, _gameObject->getRotation() + axis);
	}
	else {
		_gameObject->setRotation(angle, axis);
	}
	_modelToUpdate = true;
}

bool TransformComponent::modelNeedsToUpdate() const
{
	return _modelToUpdate;
}

void TransformComponent::updateModel(glm::mat4 parentModel)
{
	_model = glm::mat4(1.0f);
	_model = glm::translate(_model, _gameObject->getPosition());
	if (_gameObject->getRotationAngle() != 0.0f && _gameObject->getRotation() != glm::vec3(0.0f)) {
		_model = glm::rotate(_model, glm::radians(_gameObject->getRotationAngle()), _gameObject->getRotation());
	}
	_model = glm::scale(_model, _gameObject->getScale());
	_model = parentModel * _model;
	_normalMat = glm::inverse(glm::transpose(glm::mat3(_model)));

	std::vector<GameObject*> children = _gameObject->getChildren();
	for (auto it = children.begin(); it < children.end(); it++) {
		TransformComponent* com = (*it)->getComponent<TransformComponent>(ComponentType::TRANSFORM_COMPONENT);
		if (com != nullptr) {
			com->updateModel(_model);
		}
	}
	_modelToUpdate = false;
}

void TransformComponent::renderMatrix(Shader* shader) const
{
	shader->set("model", _model);
	shader->set("normalMat", _normalMat);
}
