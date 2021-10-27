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
    std::vector<std::vector<unsigned int>> indexGrid;

    unsigned int index = 0;
    float x = 0;
    float z = 0;
    for (int row = 0; row <= rows; ++row) {
        std::vector<unsigned int> indexRow;
        for (int col = 0; col <= columns; ++col) {
            x = m_width * static_cast<float>(col) / static_cast<float>(columns);
            z = m_height * static_cast<float>(row) / static_cast<float>(rows);

            m_vertices.emplace_back(x, 0, z);
            indexRow.emplace_back(index++);  // As the grid is built, build a 2D index array
        }
        indexGrid.emplace_back(indexRow);
    }

    // The grid is built from (0,0) into the bottom right quadrant. The calculated values are
    // shifted to account for this; a model transformation will work visually, but not
    // practically with the uniform grid

    glm::mat4 translation = glm::translate(
        glm::mat4(1.0f), glm::vec3(-m_width / 2.0f, 0.5f, -m_height / 2.0f));  // raise and centre
    for (auto& vertex : m_vertices) {
        vertex = glm::vec3(translation * glm::vec4(vertex, 1.0f));
    }

    // Use the index grid to create the grid cells that maintain and draw themselves
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            m_gridCells.emplace_back(
                m_vertices[indexGrid[row][col]], m_vertices[indexGrid[row][col + 1]],
                m_vertices[indexGrid[row + 1][col + 1]], m_vertices[indexGrid[row + 1][col]]);
        }
    }
}

void UGrid2D::draw() {
    for (auto& cell : m_gridCells) {
        cell.draw(m_camera);
    }
}