#pragma once

#include <memory>

#include "Camera.h"
#include "LightManager.h"
#include "Transformation.h"
#include "api/Shader.h"
#include "collision/Collider.h"
#include "model/Model.h"

enum class ObjectShape { RECTANGULAR, TRIANGULAR, SPHERICAL, CYLINDRICAL };

class Object {
public:
    Object(Model model, ShaderPath path);
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) = 0;

protected:
    Transformation m_transformation;
    Model m_model;
    Collider m_collider;
    Shader m_shader;
};
