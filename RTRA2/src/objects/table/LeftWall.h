#pragma once

#include <memory>

#include "Wall.h"
#include "model/Model.h"
#include "objects/Transformation.h"

class Camera;
class LightManager;
class Skybox;

class LeftWall : public Wall {
public:
    LeftWall(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
             ObjectType objectType, std::shared_ptr<Skybox> skybox);
    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) override;
};
