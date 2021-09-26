#include "Transformation.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Transformation::Transformation()
	: m_translation(glm::vec3(0.0f))
	, m_axis(glm::vec3(1.0f))
	, m_degrees(0)
	, m_scale(glm::vec3(1.0f)) {}

void Transformation::setTranslation(glm::vec3 translation) {
	m_translation = translation;
}

void Transformation::setRotation(glm::vec3 axis, float degrees) {
	m_axis = axis;
	m_degrees = degrees;
}

void Transformation::rotateByDegrees(float degrees) {
	m_degrees += degrees;
	if (m_degrees > 360) {
		m_degrees = 0;
	}
}

void Transformation::setScaling(glm::vec3 scale) {
	m_scale = scale;
}

const glm::mat4 Transformation::getModelMatrix() const {
	glm::mat4 transformation = glm::mat4(1.0f);
	transformation = glm::translate(transformation, m_translation);
	transformation = glm::rotate(transformation, glm::radians(m_degrees), m_axis);
	transformation = glm::scale(transformation, m_scale);
	return transformation;
}
