#pragma once

#include <memory>
#include <vector>

#include "Camera.h"
#include "Transformation.h"
#include "api/Shader.h"
#include "glm/glm.hpp"
#include "model/Model.h"

class BoundingBox {
public:
    BoundingBox(const Model& model);
    void update(const Transformation& transform);
    void draw(std::shared_ptr<Camera> camera);
    void recalculateBoundingBox();

    glm::vec3 getMin();
    glm::vec3 getMax();

private:
    std::shared_ptr<Shader> m_bbShader;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_IBO;

    std::vector<glm::vec3> m_originalVertices;

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::uvec3> m_indices;

    glm::vec3 m_min;
    glm::vec3 m_max;

    Transformation m_transform;
};