#pragma once

#include <memory>

#include "Wall.h"
#include "model/Model.h"
#include "objects/Transformation.h"

class Camera;
class LightManager;
class Skybox;

class TopWall : public Wall {
public:
    TopWall(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
            ObjectType objectType, std::shared_ptr<Skybox> skybox);
};
