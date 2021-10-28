#include "UGrid2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "objects/Object.h"

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

std::vector<std::shared_ptr<GridCell>> UGrid2D::getCellsWithObject(std::shared_ptr<Object> object) {
    glm::vec3 bbMin = object->getBoundingBox().getMin();
    glm::vec3 bbMax = object->getBoundingBox().getMax();

    int startX = glm::floor(bbMin.x / m_cellLength + (float)m_columns / 2.0f);
    int endX = glm::ceil(bbMax.x / m_cellLength + (float)m_columns / 2.0f);

    int startZ = glm::floor(bbMin.z / m_cellLength + (float)m_rows / 2.0f);
    int endZ = glm::ceil(bbMax.z / m_cellLength + (float)m_rows / 2.0f);

    // Objects outside the bounds of the defined grid can be ignored
    startX = startX < 0 ? 0 : startX;
    startZ = startZ < 0 ? 0 : startZ;
    endX = endX < m_columns ? endX : m_columns;
    endZ = endZ < m_rows ? endZ : m_rows;

    std::vector<std::shared_ptr<GridCell>> cells;
    for (int z = startZ; z < endZ; ++z) {
        std::vector<std::shared_ptr<GridCell>> row = m_gridCells[z];
        for (int x = startX; x < endX; ++x) {
            cells.push_back(row[x]);
        }
    }
    return cells;
}

void UGrid2D::clearCellsOfObject(std::shared_ptr<Object> object) {
    for (auto& row : m_gridCells) {
        for (auto& cell : row) {
            cell->remove(object);
        }
    }
}

void UGrid2D::updateObjectMembership(std::shared_ptr<Object> object) {
    std::vector<std::shared_ptr<GridCell>> memberCells = getCellsWithObject(object);
    for (auto& cell : memberCells) {
        cell->add(object);
    }
}

void UGrid2D::draw() {
    for (auto& row : m_gridCells) {
        for (auto& cell : row) {
            cell->draw(m_camera);
        }
    }
}

std::vector<std::vector<std::shared_ptr<GridCell>>> UGrid2D::getCells() { return m_gridCells; }

unsigned int UGrid2D::getNumRows() { return m_rows; }

unsigned int UGrid2D::getNumCols() { return m_columns; }

float UGrid2D::getCellLength() { return m_cellLength; }