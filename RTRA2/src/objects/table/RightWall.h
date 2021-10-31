#pragma once

#include "Camera.h"
#include "LightManager.h"
#include "Object.h"
#include "Wall.h"

class Skybox;

class RightWall : public Wall {
public:
    RightWall(std::shared_ptr<Skybox> skybox);
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) override;
};