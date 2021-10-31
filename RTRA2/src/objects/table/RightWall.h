#pragma once

#include "Wall.h"
#include "model/Model.h"
#include "objects/Transformation.h"

class Camera;
class LightManager;
class Skybox;

class RightWall : public Wall {
public:
    RightWall(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
              ObjectType objectType, std::shared_ptr<Skybox> skybox);
};
