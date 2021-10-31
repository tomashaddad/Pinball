#pragma once

#include <memory>
#include <string>

#include "model/Model.h"
#include "objects/Object.h"
#include "objects/Transformation.h"

class Shader;
class Skybox;

class Wall : public Object {
public:
    Wall(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
         ObjectType objectType, std::shared_ptr<Skybox> skybox);

    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) = 0;

protected:
    std::shared_ptr<Skybox> m_skybox;
};
