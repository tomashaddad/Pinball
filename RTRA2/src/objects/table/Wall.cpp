#include "Wall.h"

Wall::Wall(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
           ObjectType objectType, std::shared_ptr<Skybox> skybox)
    : Object(model, shader, transformation, objectType)
    , m_skybox(skybox) {}