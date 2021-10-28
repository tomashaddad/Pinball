#include "BoundingBox.h"

#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <limits>

BoundingBox::BoundingBox(const Model& model)
    : m_bbShader(
          std::make_shared<Shader>("./src/shaders/bbox/bbox.vert", "./src/shaders/bbox/bbox.frag"))
    , m_VAO(0)
    , m_VBO(0)
    , m_IBO(0)
    , m_min(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_max(glm::vec3(0.0f, 0.0f, 0.0f)) {
    // Calculate initial bounding box on instantiation of the object
    for (auto& mesh : model.m_meshes) {
        m_min.x = std::min(mesh.m_min.x, m_min.x);
        m_min.y = std::min(mesh.m_min.y, m_min.y);
        m_min.z = std::min(mesh.m_min.z, m_min.z);
        m_max.x = std::max(mesh.m_max.x, m_max.x);
        m_max.y = std::max(mesh.m_max.y, m_max.y);
        m_max.z = std::max(mesh.m_max.z, m_max.z);
    }

    // clang-format off

    m_vertices.insert(m_vertices.end(), {
        // front
        {m_min.x, m_min.y, m_max.z},
        {m_max.x, m_min.y, m_max.z},
        {m_max.x, m_max.y, m_max.z},
        {m_min.x, m_max.y, m_max.z},
        // back
        {m_min.x, m_min.y, m_min.z},
        {m_max.x, m_min.y, m_min.z},
        {m_max.x, m_max.y, m_min.z},
        {m_min.x, m_max.y, m_min.z}
    });

    m_originalVertices = m_vertices;

    // vertices for a cube of triangles
    m_indices.insert(m_indices.end(), {
		{0, 1, 2}, {2, 3, 0}, // front
		{1, 5, 6}, {6, 2, 1}, // right
		{7, 6, 5}, {5, 4, 7}, // back
		{4, 0, 3}, {3, 7, 4}, // left
		{4, 5, 1}, {1, 0, 4}, // bottom
		{3, 2, 6}, {6, 7, 3}  // top
    });

    // clang-format on

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3),
                 glm::value_ptr(m_vertices[0]), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec3),
                 glm::value_ptr(m_indices[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BoundingBox::update(const Transformation& transform) {
    glm::mat4 model = transform.getModelMatrix();

    for (auto i = 0; i < m_originalVertices.size(); ++i) {
        m_vertices[i] = glm::vec3(model * glm::vec4(m_originalVertices[i], 1.0f));
    }

    recalculateBoundingBox();

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(glm::vec3),
                    glm::value_ptr(m_vertices[0]));
}

void BoundingBox::recalculateBoundingBox() {
    m_min = std::numeric_limits<float>::max() * glm::vec3(1.0f);
    m_max = std::numeric_limits<float>::max() * glm::vec3(-1.0f);

    for (auto& value : m_vertices) {
        m_min.x = std::min(value.x, m_min.x);
        m_min.y = std::min(value.y, m_min.y);
        m_min.z = std::min(value.z, m_min.z);
        m_max.x = std::max(value.x, m_max.x);
        m_max.y = std::max(value.y, m_max.y);
        m_max.z = std::max(value.z, m_max.z);
    }

    double hW = (m_max.x - m_min.x) / 2.0f;
    double hH = (m_max.y - m_min.y) / 2.0f;
    double hD = (m_max.z - m_min.z) / 2.0f;

    m_vertices.clear();

    // clang-format off

    m_vertices.insert(m_vertices.end(), {
        // front
        {m_min.x, m_min.y, m_max.z},
        {m_max.x, m_min.y, m_max.z},
        {m_max.x, m_max.y, m_max.z},
        {m_min.x, m_max.y, m_max.z},
        // back
        {m_min.x, m_min.y, m_min.z},
        {m_max.x, m_min.y, m_min.z},
        {m_max.x, m_max.y, m_min.z},
        {m_min.x, m_max.y, m_min.z}
    });

    // clang-format on
}

void BoundingBox::draw(std::shared_ptr<Camera> camera) {
    m_bbShader->bind();
    m_bbShader->setMat4("model", glm::mat4(1.0f));
    m_bbShader->setMat4("view", camera->getViewMatrix());
    m_bbShader->setMat4("projection", camera->getProjectionMatrix());

    glBindVertexArray(m_VAO);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);

    glDrawElements(GL_TRIANGLES, m_indices.size() * sizeof(glm::uvec3), GL_UNSIGNED_INT, 0);

    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

glm::vec3 BoundingBox::getMin() { return m_min; }

glm::vec3 BoundingBox::getMax() { return m_max; }