#pragma once

#include "Camera.h"
#include "LightManager.h"
#include "Object.h"

class TopWall : public Object {
public:
    TopWall();
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) override;
};
