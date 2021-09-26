#pragma once

#include "Camera.h"
#include <memory>
#include <vector>

#include <glm/glm.hpp>

enum class LightType {
	DIRECTIONAL = 0,
	POINT = 1
};

struct Light {
	LightType type;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct DirectionalLight : public Light {
	glm::vec3 direction;
};

struct PointLight : public Light {
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
};

class LightManager {
public:
	LightManager(std::shared_ptr<Camera> camera);

	void addPointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		glm::vec3 position, float constant, float linear, float quadratic);
	const DirectionalLight& getDirectionalLight() const;
	const std::vector<PointLight>& getPointLights() const;
	const float getTypeAsFloat(Light light) const;
private:
	std::shared_ptr<Camera> m_camera;

	DirectionalLight m_directional;
	std::vector<PointLight> m_pointLights;
};