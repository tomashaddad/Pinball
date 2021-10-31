#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class Shader;

class LightManager {
public:
    LightManager(std::shared_ptr<Camera> camera);

    void drawPointLights();
    void updatePointLights(double dt);

    void addPointLight(std::shared_ptr<Shader> shader, glm::vec3 ambient, glm::vec3 diffuse,
                       glm::vec3 specular, float radius, float constant, float linear,
                       float quadratic, double sideLength);
    const DirectionalLight& getDirectionalLight();
    const std::vector<PointLight>& getPointLights() const;
    const unsigned int getMaxPointLights() const;
    const unsigned int sizeOfPointLights() const;

private:
    std::shared_ptr<Camera> m_camera;

    unsigned int m_maxPointLights;

    DirectionalLight m_directional;
    std::vector<PointLight> m_pointLights;
};