#pragma once
#include "scene/SceneBase.h"

#include "Camera.h"
#include "api/Shader.h"
#include "textures/Model.h"

#include <memory>

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