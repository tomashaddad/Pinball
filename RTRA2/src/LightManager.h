#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Camera.h"

enum class LightType { DIRECTIONAL = 0, POINT = 1 };

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

    void addPointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position,
                       float constant, float linear, float quadratic);
    const DirectionalLight& getDirectionalLight();
    const std::vector<PointLight>& getPointLights() const;
    const float getTypeAsFloat(Light light) const;
    const unsigned int getMaxPointLights() const;
    const unsigned int sizeOfPointLights() const;

private:
    std::shared_ptr<Camera> m_camera;

    unsigned int m_maxPointLights;

    DirectionalLight m_directional;
    std::vector<PointLight> m_pointLights;
};