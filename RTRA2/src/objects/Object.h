#pragma once

#include <memory>

#include "Camera.h"
#include "LightManager.h"
#include "Transformation.h"
#include "api/Shader.h"
#include "collision/Collider.h"
#include "model/Model.h"

class Object {
public:
    Object(Model model, ShaderPath path, Collider collider);
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) = 0;

protected:
    Transformation m_transformation;
    Collider m_collider;
    Model m_model;
    Shader m_shader;
};
