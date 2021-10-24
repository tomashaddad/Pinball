#include "Collider.h"

#include <algorithm>
#include <iostream>

Collider::Collider(Model& model) {
    for (auto& mesh : model.m_meshes) {
        m_boundingBox.min.x = std::min(mesh.m_boundingBox.min.x, m_boundingBox.min.x);
        m_boundingBox.min.y = std::min(mesh.m_boundingBox.min.y, m_boundingBox.min.y);
        m_boundingBox.min.z = std::min(mesh.m_boundingBox.min.z, m_boundingBox.min.z);
        m_boundingBox.max.x = std::max(mesh.m_boundingBox.max.x, m_boundingBox.max.x);
        m_boundingBox.max.y = std::max(mesh.m_boundingBox.max.y, m_boundingBox.max.y);
        m_boundingBox.max.z = std::max(mesh.m_boundingBox.max.z, m_boundingBox.max.z);
    }
}

void Collider::update(Transformation& transformation) {
    m_boundingBox.min = transformation.getModelMatrix() * m_boundingBox.min;
    m_boundingBox.max = transformation.getModelMatrix() * m_boundingBox.max;

    std::cout << m_boundingBox.max.x << " " << m_boundingBox.max.y << " " << m_boundingBox.max.z
              << std::endl;
}