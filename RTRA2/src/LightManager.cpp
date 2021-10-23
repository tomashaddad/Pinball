#include "LightManager.h"

LightManager::LightManager(std::shared_ptr<Camera> camera)
    : m_camera(camera)
    , m_maxPointLights(4) {
    // white above board
    addPointLight(glm::vec3(0.1f), glm::vec3(0.8f), glm::vec3(0.8f), glm::vec3(0.0f, 5.0f, 0.0f),
                  1.0f, 0.045, 0.0075);
    m_directional = DirectionalLight({{LightType::DIRECTIONAL, glm::vec3(0.2f, 0.2f, 0.2f),
                                       glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f)},
                                      m_camera->getForwardVector()});
}

void LightManager::addPointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
                                 glm::vec3 position, float constant, float linear,
                                 float quadratic) {
    m_pointLights.push_back(PointLight(
        {{LightType::POINT, ambient, diffuse, specular}, position, constant, linear, quadratic}));
}

const DirectionalLight& LightManager::getDirectionalLight() {
    m_directional.direction = m_camera->getForwardVector();
    return m_directional;
}

const std::vector<PointLight>& LightManager::getPointLights() const { return m_pointLights; }

const float LightManager::getTypeAsFloat(Light light) const {
    return light.type == LightType::POINT ? 1.0 : 0.0;
}

const unsigned int LightManager::sizeOfPointLights() const { return m_pointLights.size(); }

const unsigned int LightManager::getMaxPointLights() const { return m_maxPointLights; };