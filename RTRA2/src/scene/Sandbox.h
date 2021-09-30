#pragma once
#include <memory>

#include "Camera.h"
#include "api/Shader.h"
#include "scene/SceneBase.h"
#include "textures/Model.h"

class Sandbox : public SceneBase {
public:
    Sandbox(std::shared_ptr<Camera> camera);
    ~Sandbox();
    void render() override;

private:
    std::shared_ptr<Camera> m_camera;
    Shader m_bagShader;
    Model m_bagModel;
};