#include "Ball.h"

#include "Backboard.h"
#include "collision/Physics.h"
#include "scene/Skybox.h"

Ball::Ball(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
           ObjectType objectType, std::shared_ptr<Skybox> skybox)
    : Object(model, shader, transformation, objectType)
    , m_skybox(skybox)
    , m_velocity(glm::vec3(0.0, 0.0f, 0.0f))
    , m_acceleration(glm::vec3(0.0f)) {
    m_radius = (m_boundingBox.getMax().x - m_boundingBox.getMin().x) / 2.0f;
}

void Ball::update(float dt, std::shared_ptr<Physics> physics) {
    Object::update(dt, physics);
    m_acceleration = physics->getGravity();
    m_velocity += m_acceleration * dt;
    m_transformation.m_translation += m_velocity * dt + 0.5f * m_acceleration * dt * dt;
}

void Ball::draw(std::shared_ptr<Camera> camera, std::shared_ptr<LightManager> lightManager) {
    glm::mat4 model = m_transformation.getModelMatrix();
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();

    m_shader->bind();

    m_shader->setMat4("model", model);
    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);
    m_shader->setVec3f("viewPos", camera->getPosition());
    m_shader->setDirectionalLight("directionalLight", lightManager->getDirectionalLight());
    m_shader->setInt("lightNumber", lightManager->sizeOfPointLights());

    for (int i = 0; i < lightManager->sizeOfPointLights(); ++i) {
        m_shader->setPointLight("pointLights", lightManager->getPointLights()[i], i);
    }

    m_model.draw(m_shader, m_skybox->getTextureID());
}

void Ball::bounce(double scalar) {
    m_velocity.y *= -scalar;
    m_transformation.m_translation.y += 0.02;
}

double Ball::getRadius() { return m_radius; }