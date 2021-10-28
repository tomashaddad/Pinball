#include "PinballScene.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "api/Shader.h"
#include "objects/Backboard.h"
#include "objects/BottomWall.h"
#include "objects/LeftWall.h"
#include "objects/RightWall.h"
#include "objects/SideBit.h"
#include "objects/TopWall.h"

PinballScene::PinballScene(std::shared_ptr<Camera> camera,
                           std::shared_ptr<LightManager> lightManager)
    : m_camera(camera)
    , m_skybox(camera)
    , m_lightManager(lightManager)
    , m_uGrid2D(std::make_shared<UGrid2D>(17, 10, 0.5, camera)) {
    m_objects.push_back(std::make_shared<Backboard>());
    m_objects.push_back(std::make_shared<LeftWall>());
    m_objects.push_back(std::make_shared<RightWall>());
    m_objects.push_back(std::make_shared<TopWall>());
    m_objects.push_back(std::make_shared<BottomWall>());
    m_objects.push_back(std::make_shared<SideBit>());
}

void PinballScene::update(float dt) {
    for (auto& object : m_objects) {
        m_uGrid2D->clearCellsOfObject(object);
        object->update(dt);
        m_uGrid2D->updateObjectMembership(object);
    }
}

void PinballScene::render() {
    for (auto& object : m_objects) {
        object->draw(m_camera, m_lightManager);
        object->drawBoundingBox(m_camera);
    }

    m_uGrid2D->draw();

    // draw last
    m_skybox.draw();
}