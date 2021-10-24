#pragma once

#include "glm/glm.hpp"

class BoundingBox {
public:
    glm::vec4 min = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 max = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

private:
};