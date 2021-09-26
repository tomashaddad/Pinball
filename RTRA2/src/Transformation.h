#pragma once

#include <glm/glm.hpp>

class Transformation {
public:
	Transformation();
	void setTranslation(glm::vec3 translation);
	void setRotation(glm::vec3 axis, float degrees = 0);
	void rotateByDegrees(float degrees);
	void setScaling(glm::vec3 scale);
	const glm::mat4 getModelMatrix() const;

private:
	glm::vec3 m_translation;
	glm::vec3 m_axis;
	float m_degrees;
	glm::vec3 m_scale;
};