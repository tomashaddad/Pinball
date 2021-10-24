#pragma once

#include <memory>

#include "Camera.h"
#include "LightManager.h"
#include "Object.h"

class Backboard : public Object {
public:
    Backboard();
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) override;
};
