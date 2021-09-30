#include "LightManager.h"

LightManager::LightManager(std::shared_ptr<Camera> camera)
    : m_camera(camera) {
    // m_directional is updated per frame

    float dir = 5.0f;  // direction
    float in = 0.8;    // intensity

    // white
    addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(in, in, in), glm::vec3(in, in, in),
                  glm::vec3(dir, dir, dir), 1.0f, 0.045, 0.0075);

    // red
    addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(in, 0.0, 0.0), glm::vec3(in, 0.0, 0.0),
                  glm::vec3(dir, dir, -dir), 1.0f, 0.045, 0.0075);

    // yellow
    addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(in, in, 0.0), glm::vec3(in, in, 0.0),
                  glm::vec3(dir, -dir, dir), 1.0f, 0.045, 0.0075);

    // pink
    addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(in, 0.0, in), glm::vec3(in, 0.0, in),
                  glm::vec3(dir, -dir, -dir), 1.0f, 0.045, 0.0075);

    // green
    addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0, in, 0.0), glm::vec3(0.0, in, 0.0),
                  glm::vec3(-dir, dir, dir), 1.0f, 0.045, 0.0075);

    // purple
    addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.5 * in, 0.0, in),
                  glm::vec3(0.5 * in, 0.0, in), glm::vec3(-dir, dir, -dir), 1.0f, 0.045, 0.0075);

    // orange
    addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(in, 0.5 * in, 0.0),
                  glm::vec3(in, 0.5 * in, 0.0), glm::vec3(-dir, -dir, dir), 1.0f, 0.045, 0.0075);

    // blue
    addPointLight(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0, 0.0, in), glm::vec3(0.0, 0.0, in),
                  glm::vec3(-dir, -dir, -dir), 1.0f, 0.045, 0.0075);
}

void LightManager::addPointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
                                 glm::vec3 position, float constant, float linear,
                                 float quadratic) {
    m_pointLights.push_back(PointLight(
        {{LightType::POINT, ambient, diffuse, specular}, position, constant, linear, quadratic}));
}

const DirectionalLight& LightManager::getDirectionalLight() const {
    return DirectionalLight({{LightType::DIRECTIONAL, glm::vec3(0.2f, 0.2f, 0.2f),
                              glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f)},
                             m_camera->getForwardVector()});
}

const std::vector<PointLight>& LightManager::getPointLights() const { return m_pointLights; }

const float LightManager::getTypeAsFloat(Light light) const {
    return light.type == LightType::POINT ? 1.0 : 0.0;
}