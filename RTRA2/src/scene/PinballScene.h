#pragma once
#include <memory>
#include <vector>

#include "Camera.h"
#include "LightManager.h"
#include "Skybox.h"
#include "api/Shader.h"
#include "collision/UGrid2D.h"
#include "model/Model.h"
#include "objects/Object.h"

class PinballScene {
public:
    PinballScene(std::shared_ptr<Camera> camera, std::shared_ptr<LightManager> lightManager);
    void update(float dt);
    void render();

private:
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<LightManager> m_lightManager;
    std::vector<std::shared_ptr<Object>> m_objects;

    std::shared_ptr<UGrid2D> m_uGrid2D;
    Skybox m_skybox;
};