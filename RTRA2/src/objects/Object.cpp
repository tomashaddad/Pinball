#include "Object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Object::Object(std::string modelPath, std::shared_ptr<Shader> shader)
    : m_model(modelPath)
    , m_shader(shader)
    , m_boundingBox(m_model) {}

void Object::drawBoundingBox(std::shared_ptr<Camera> camera) { m_boundingBox.draw(camera); }
