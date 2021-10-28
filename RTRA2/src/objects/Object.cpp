#include "Object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "collision/UGrid2D.h"

Object::Object(std::string modelPath, std::shared_ptr<Shader> shader)
    : m_model(modelPath)
    , m_shader(shader)
    , m_boundingBox(m_model) {}

void Object::update(float dt) {
    // m_transformation.m_rotation = glm::angleAxis(glm::radians(.1f), glm::vec3(1.0f, 0.0f, 0.0f))
    // *
    //                              m_transformation.m_rotation;
    m_boundingBox.update(m_transformation);
}

void Object::drawBoundingBox(std::shared_ptr<Camera> camera) { m_boundingBox.draw(camera); }

BoundingBox Object::getBoundingBox() { return m_boundingBox; }