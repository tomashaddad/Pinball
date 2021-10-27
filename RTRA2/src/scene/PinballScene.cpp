#include "PinballScene.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "api/Shader.h"
#include "objects/Backboard.h"

PinballScene::PinballScene(std::shared_ptr<Camera> camera,
                           std::shared_ptr<LightManager> lightManager)
    : m_camera(camera)
    , m_skybox(camera)
    , m_lightManager(lightManager) {
    m_objects.push_back(std::make_shared<Backboard>());
}

void PinballScene::render() {
    for (auto& object : m_objects) {
        object->draw(m_camera, m_lightManager);
        object->drawBoundingBox(m_camera);
    }

    m_skybox.draw();
}