#pragma once

#include "Camera.h"
#include "LightManager.h"
#include "Object.h"
#include "Wall.h"

class Skybox;

class BottomWall : public Wall {
public:
    BottomWall(std::shared_ptr<Skybox> skybox);
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) override;
};
