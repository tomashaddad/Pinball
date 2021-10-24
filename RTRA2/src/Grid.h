#pragma once

#include <memory>
#include <vector>

#include "Camera.h"
#include "Transformation.h"
#include "api/Shader.h"
#include "glm/glm.hpp"

class Grid {
public:
    Grid(unsigned int rows, unsigned int columns, float cellLength);
    void draw(std::shared_ptr<Camera> camera);

private:
    Shader m_gridShader;
    Transformation m_transform;

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::uvec4> m_indices;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_IBO;

    unsigned int m_length;
    unsigned int m_rows;
    unsigned int m_columns;
    float m_cellLength;
    float m_width;
    float m_height;
};
