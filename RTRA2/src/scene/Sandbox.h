#pragma once
#include <memory>

#include "Camera.h"
#include "Skybox.h"
#include "api/Shader.h"
#include "scene/SceneBase.h"
#include "textures/Model.h"

class Sandbox : public SceneBase {
public:
    Sandbox(std::shared_ptr<Camera> camera);
    void render() override;

private:
    std::shared_ptr<Camera> m_camera;
    Shader m_bagShader;
    Model m_bagModel;
    Skybox m_skybox;
};