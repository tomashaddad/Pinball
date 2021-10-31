#pragma once

#include <memory>

#include "Camera.h"
#include "LightManager.h"
#include "Object.h"
#include "Wall.h"

class Skybox;

class TopWall : public Wall {
public:
    TopWall(std::shared_ptr<Skybox> skybox);
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) override;
};
