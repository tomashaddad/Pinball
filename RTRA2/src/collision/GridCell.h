#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Camera.h"
#include "api/Shader.h"
#include "objects/Object.h"

class GridCell {
public:
    GridCell(glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomRight, glm::vec3 bottomLeft);
    void draw(std::shared_ptr<Camera> camera);
    void add(std::shared_ptr<Object> object);
    bool has(std::shared_ptr<Object> object);
    void remove(std::shared_ptr<Object> object);

    std::vector<std::shared_ptr<Object>> getMemberObjects();

private:
    std::shared_ptr<Shader> m_gridShader;
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_IBO;
    std::vector<glm::vec3> m_vertices;
    static std::vector<glm::uvec2> m_indices;

    // The objects which sit within this cell's boundaries
    std::vector<std::shared_ptr<Object>> m_objects;
};
