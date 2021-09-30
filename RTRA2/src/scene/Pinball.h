#pragma once
#include <memory>

#include "Camera.h"
#include "SceneBase.h"

class Pinball : public SceneBase {
public:
    Pinball(std::shared_ptr<Camera> camera);
    void render() override;

private:
    std::shared_ptr<Camera> m_camera;
};