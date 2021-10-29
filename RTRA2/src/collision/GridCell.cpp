#include "GridCell.h"

#include <glad/glad.h>

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

std::vector<glm::uvec2> GridCell::m_indices = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};

GridCell::GridCell(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomRight,
                   glm::vec3 bottomLeft)
    : m_gridShader(
          std::make_shared<Shader>("./src/shaders/grid/grid.vert", "./src/shaders/grid/grid.frag"))
    , m_VAO(0)
    , m_VBO(0)
    , m_IBO(0) {
    m_vertices.insert(m_vertices.end(), {topLeft, topRight, bottomRight, bottomLeft});

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec2),
                 glm::value_ptr(m_indices[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GridCell::add(std::shared_ptr<Object> object) {
    if (!has(object)) {
        m_objects.push_back(object);
    }
}

bool GridCell::has(std::shared_ptr<Object> object) {
    return std::find(m_objects.begin(), m_objects.end(), object) != m_objects.end();
}

void GridCell::remove(std::shared_ptr<Object> object) {
    m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void GridCell::draw(std::shared_ptr<Camera> camera) {
    m_gridShader->bind();
    m_gridShader->setMat4("model", glm::mat4(1.0f));  // not using a transform
    m_gridShader->setMat4("view", camera->getViewMatrix());
    m_gridShader->setMat4("projection", camera->getProjectionMatrix());

    if (m_objects.size() == 1) {
        m_gridShader->setVec3f("colour", glm::vec3(0.0f, 1.0f, 0.0f));
    } else if (m_objects.size() == 0) {
        m_gridShader->setVec3f("colour", glm::vec3(1.0f, 1.0f, 1.0f));
    } else {
        m_gridShader->setVec3f("colour", glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glBindVertexArray(m_VAO);
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

std::vector<std::shared_ptr<Object>> GridCell::getMemberObjects() { return m_objects; }