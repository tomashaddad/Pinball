#include "Grid.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "glad/glad.h"

/*
    An std::vector of dimensions rows * columns are filled with the corresponding
    indices of the grid to be drawn. Then, the four indices of each cell are added
    to the indices array as pairs so that the grid can be drawn as GL_LINES.
*/

Grid::Grid(std::shared_ptr<Camera> camera, unsigned int rows, unsigned int columns,
           float cellLength)
    : m_gridShader("./src/shaders/grid/grid.vert", "./src/shaders/grid/grid.frag")
    , m_camera(camera) {
    std::vector<std::vector<unsigned int>> indexGrid;

    unsigned int index = 0;
    float width = cellLength * columns;
    float height = cellLength * rows;

    for (int row = 0; row <= rows; ++row) {
        std::vector<unsigned int> indexRow;
        for (int col = 0; col <= columns; ++col) {
            float x = width * ((float)col / (float)columns);
            float z = height * ((float)row / (float)rows);

            m_vertices.emplace_back(x, 0, z);
            indexRow.emplace_back(index++);
        }
        indexGrid.emplace_back(indexRow);
    }

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            m_indices.emplace_back(indexGrid[row][col], indexGrid[row][col + 1],
                                   indexGrid[row][col + 1], indexGrid[row + 1][col + 1]);
            m_indices.emplace_back(indexGrid[row + 1][col + 1], indexGrid[row + 1][col],
                                   indexGrid[row + 1][col], indexGrid[row][col]);
        }
    }

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3),
                 glm::value_ptr(m_vertices[0]), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec4),
                 glm::value_ptr(m_indices[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_length = (unsigned int)m_indices.size() * 4;
}

void Grid::draw() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 projection = m_camera->getProjectionMatrix();

    m_gridShader.bind();

    m_gridShader.setMat4("model", model);
    m_gridShader.setMat4("view", view);
    m_gridShader.setMat4("projection", projection);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_LINES, m_length, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}