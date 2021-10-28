#include "UGrid2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

UGrid2D::UGrid2D(unsigned int rows, unsigned int columns, float cellLength,
                 std::shared_ptr<Camera> camera)
    : m_gridShader(
          std::make_shared<Shader>("./src/shaders/grid/grid.vert", "./src/shaders/grid/grid.frag"))
    , m_rows(rows)
    , m_columns(columns)
    , m_cellLength(cellLength)
    , m_camera(camera)
    , m_width(cellLength * columns)
    , m_height(cellLength * rows) {
    glm::vec3 vertex = glm::vec3(0.0f, 0.5f, 0.0f);  // grid floats above for drawing purposes
    std::vector<glm::vec3> vertexRow;
    for (int row = 0; row <= rows; ++row) {
        for (int col = 0; col <= columns; ++col) {
            vertex.x =
                m_width * static_cast<float>(col) / static_cast<float>(columns) - m_width / 2.0f;
            vertex.z =
                m_height * static_cast<float>(row) / static_cast<float>(rows) - m_height / 2.0f;
            vertexRow.push_back(vertex);
        }
        m_vertices.emplace_back(vertexRow);
        vertexRow.clear();
    }

    std::vector<std::shared_ptr<GridCell>> cellRow;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            cellRow.emplace_back(
                std::make_shared<GridCell>(m_vertices[row][col], m_vertices[row][col + 1],
                                           m_vertices[row + 1][col + 1], m_vertices[row + 1][col]));
        }
        m_gridCells.emplace_back(cellRow);
        cellRow.clear();
    }
}

void UGrid2D::draw() {
    for (auto& row : m_gridCells) {
        for (auto& cell : row) {
            cell->draw(m_camera);
        }
    }
}