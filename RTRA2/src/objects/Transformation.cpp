#include "Transformation.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Transformation::Transformation()
    : m_scale(glm::vec3(1.0f))
    , m_rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
    , m_translation(glm::vec3(0.0f)) {}

Transformation::Transformation(glm::vec3 scale, glm::quat rotation, glm::vec3 translation)
    : m_scale(scale)
    , m_rotation(rotation)
    , m_translation(translation) {}

glm::mat4 Transformation::getModelMatrix() const {
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, m_translation);  // translate
    transformation = transformation * glm::toMat4(m_rotation);       // rotate
    transformation = glm::scale(transformation, m_scale);            // scale
    return transformation;
}
