#pragma once

#include <memory>
#include <vector>

#include "Camera.h"
#include "GridCell.h"
#include "Transformation.h"
#include "api/Shader.h"
#include "glm/glm.hpp"

class UGrid2D {
public:
    UGrid2D(unsigned int rows, unsigned int columns, float cellLength,
            std::shared_ptr<Camera> camera);
    void draw();

private:
    std::shared_ptr<Shader> m_gridShader;
    std::shared_ptr<Camera> m_camera;
    Transformation m_transform;

    std::vector<std::vector<std::shared_ptr<GridCell>>> m_gridCells;
    std::vector<std::vector<glm::vec3>> m_vertices;

    unsigned int m_rows;
    unsigned int m_columns;
    float m_cellLength;
    float m_width;
    float m_height;
};
