#pragma once

#include <glm/glm.hpp>

class Physics {
public:
    Physics();

    glm::vec3 getGravity();

private:
    float m_gravitationalAcceleration;
    glm::vec3 m_directionOfGravity;
};
