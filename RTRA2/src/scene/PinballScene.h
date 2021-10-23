#pragma once
#include <memory>

#include "Camera.h"
#include "LightManager.h"
#include "Skybox.h"
#include "api/Shader.h"
#include "textures/Model.h"

class PinballScene {
public:
    PinballScene(std::shared_ptr<Camera> camera);
    void render();

private:
    std::shared_ptr<Camera> m_camera;
    Shader m_bagShader;
    Model m_ball;
    Skybox m_skybox;
    LightManager m_lightManager;
};