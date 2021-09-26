#pragma once
#include "SceneBase.h"

#include "Camera.h"
#include <memory>

class Pinball : public SceneBase
{
public:
	Pinball(std::shared_ptr<Camera> camera);
	void render() override;

private:
	std::shared_ptr<Camera> m_camera;
};