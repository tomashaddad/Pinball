#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Transformation {
public:
    Transformation();
    Transformation(glm::vec3 scale, glm::quat rotation, glm::vec3 translation);
    const glm::mat4 getModelMatrix() const;
    glm::vec3 m_scale;
    glm::quat m_rotation;
    glm::vec3 m_translation;
};