#include "LightManager.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "api/Shader.h"

LightManager::LightManager(std::shared_ptr<Camera> camera)
    : m_camera(camera)
    , m_maxPointLights(4)
    , m_directional(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.1f, 0.1f, 0.1f),
                    glm::vec3(0.1f, 0.1f, 0.1f), m_camera->getForwardVector()) {
    float sideLength = 0.5f;
    // fluorescent pink
    addPointLight(std::make_shared<Shader>("./src/shaders/light/light.vert",
                                           "./src/shaders/light/light.frag"),
                  glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.0f, 0.29f),
                  glm::vec3(0.8f, 0.8f, 0.8f), 8.0f, 1.0f, 0.045, 0.0075, sideLength);

    // fluorescent blue
    addPointLight(std::make_shared<Shader>("./src/shaders/light/light.vert",
                                           "./src/shaders/light/light.frag"),
                  glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.35f, 0.80f),
                  glm::vec3(0.8f, 0.8f, 0.8f), 8.0f, 1.0f, 0.045, 0.0075, sideLength);

    // fluorescent green
    addPointLight(std::make_shared<Shader>("./src/shaders/light/light.vert",
                                           "./src/shaders/light/light.frag"),
                  glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.33f, 0.8f, 0.0f),
                  glm::vec3(0.8f, 0.8f, 0.8f), 8.0f, 1.0f, 0.045, 0.0075, sideLength);

    // fluorescent yellow
    addPointLight(std::make_shared<Shader>("./src/shaders/light/light.vert",
                                           "./src/shaders/light/light.frag"),
                  glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.78f, 0.80f, 0.21f),
                  glm::vec3(0.8f, 0.8f, 0.8f), 8.0f, 1.0f, 0.045, 0.0075, sideLength);
}

void LightManager::addPointLight(std::shared_ptr<Shader> shader, glm::vec3 ambient,
                                 glm::vec3 diffuse, glm::vec3 specular, float radius,
                                 float constant, float linear, float quadratic, double sideLength) {
    m_pointLights.emplace_back(shader, ambient, diffuse, specular, radius, constant, linear,
                               quadratic, sideLength);
}

void LightManager::drawPointLights() {
    for (auto& light : m_pointLights) {
        light.draw(m_camera);
    }
}

void LightManager::updatePointLights(double dt) {
    for (auto& light : m_pointLights) {
        light.update(dt);
    }
}

const DirectionalLight& LightManager::getDirectionalLight() {
    m_directional.direction = m_camera->getForwardVector();
    return m_directional;
}

const std::vector<PointLight>& LightManager::getPointLights() const { return m_pointLights; }

const unsigned int LightManager::sizeOfPointLights() const { return m_pointLights.size(); }

const unsigned int LightManager::getMaxPointLights() const { return m_maxPointLights; };