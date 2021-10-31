#include "TopWall.h"

#include "Camera.h"
#include "lights/LightManager.h"
#include "scene/Skybox.h"

TopWall::TopWall(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
                 ObjectType objectType, std::shared_ptr<Skybox> skybox)
    : Wall(model, shader, transformation, objectType, skybox) {}
