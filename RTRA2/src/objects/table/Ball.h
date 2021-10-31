#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Camera.h"
#include "lights/LightManager.h"
#include "objects/Object.h"

class Skybox;
class Physics;

class Ball : public Object {
public:
    Ball(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
         ObjectType objectType, std::shared_ptr<Skybox> m_skybox);
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) override;
    virtual void update(float dt, std::shared_ptr<Physics> physics) override;

    double getRadius();

    void bounce(double scalar);

private:
    double m_radius;

    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;
    std::shared_ptr<Skybox> m_skybox;
};
