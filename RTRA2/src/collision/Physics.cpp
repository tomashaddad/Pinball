#include "Physics.h"

#include <glm/glm.hpp>

Physics::Physics()
    : m_directionOfGravity(glm::vec3(0.0f, -1.0f, 0.0f))
    , m_gravitationalAcceleration(.1f) {}

glm::vec3 Physics::getGravity() { return m_gravitationalAcceleration * m_directionOfGravity; }