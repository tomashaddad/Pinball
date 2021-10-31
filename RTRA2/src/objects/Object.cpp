#include "Object.h"

#include "collision/UGrid2D.h"
#include "model/Model.h"

Object::Object(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
               ObjectType type)
    : m_model(model)
    , m_shader(shader)
    , m_transformation(transformation)
    , m_type(type)
    , m_boundingBox(m_model) {}

void Object::update(float dt, std::shared_ptr<Physics> physics) {
    m_boundingBox.update(m_transformation);
}

void Object::add(std::shared_ptr<GridCell> cell) {
    if (!has(cell)) {
        m_cellMemberships.push_back(cell);
    }
}

bool Object::has(std::shared_ptr<GridCell> cell) {
    return std::find(m_cellMemberships.begin(), m_cellMemberships.end(), cell) !=
           m_cellMemberships.end();
}

void Object::remove(std::shared_ptr<GridCell> cell) {
    m_cellMemberships.erase(std::remove(m_cellMemberships.begin(), m_cellMemberships.end(), cell),
                            m_cellMemberships.end());
}

void Object::drawBoundingBox(std::shared_ptr<Camera> camera) { m_boundingBox.draw(camera); }

std::vector<std::shared_ptr<GridCell>> Object::getCellMemberships() { return m_cellMemberships; }

BoundingBox Object::getBoundingBox() { return m_boundingBox; }

ObjectType Object::type() { return m_type; }

glm::vec3 Object::getPosition() { return m_transformation.m_translation; }