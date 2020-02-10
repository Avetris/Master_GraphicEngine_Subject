#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include <engine\components\component.hpp>
#include <glm/glm.hpp>

class TransformComponent : public Component {
    public:
        TransformComponent(uint16_t UID, Handle* gameObject);
        void init();
        void update(float dt);
        ~TransformComponent();

        void move(glm::vec3 direction, bool add = false);
        void scale(glm::vec3 scale, bool add = false);
        void rotate(float angle, glm::vec3 axis, bool add = false);

        bool modelNeedsToUpdate() const;
        void updateModel(glm::mat4 parentModel = glm::mat4(1.0f));

    protected:
        glm::mat4 _model = glm::mat4(1.0f);
        glm::mat4 _normalMat = glm::mat4(1.0f);
        bool _modelToUpdate = true;
};

#endif
