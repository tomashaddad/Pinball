#pragma once

#include <memory>

#include "Camera.h"
#include "lights/LightManager.h"
#include "model/Model.h"
#include "objects/Object.h"
#include "objects/Transformation.h"

class Shader;

class Backboard : public Object {
public:
    Backboard(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
              ObjectType objectType);
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) override;
};
