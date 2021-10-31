#include "PinballScene.h"

#include <iostream>

#include "Skybox.h"
#include "collision/UGrid2D.h"
#include "collision/collision.h"
#include "gltext.h"
#include "objects//table/BottomWall.h"
#include "objects/Object.h"
#include "objects/table/Backboard.h"
#include "objects/table/Ball.h"
#include "objects/table/LeftWall.h"
#include "objects/table/RightWall.h"
#include "objects/table/TopWall.h"
#include "utility/Text.h"

PinballScene::PinballScene(std::shared_ptr<Camera> camera,
                           std::shared_ptr<LightManager> lightManager,
                           std::shared_ptr<Physics> physics, std::shared_ptr<Text> text)
    : m_camera(camera)
    , m_skybox(std::make_shared<Skybox>(camera))
    , m_lightManager(lightManager)
    , m_physics(physics)
    , m_text(text)
    , m_drawLights(false)
    , m_drawGrid(false)
    , m_drawBoundingBoxes(false)
    , m_uGrid2D(std::make_shared<UGrid2D>(17, 10, 0.5, camera))
    , m_bloomRenderer(std::make_shared<Shader>("./src/shaders/framebuffer/blur.vert",
                                               "./src/shaders/framebuffer/blur.frag"),
                      std::make_shared<Shader>("./src/shaders/framebuffer/combine.vert",
                                               "./src/shaders/framebuffer/combine.frag")) {
    m_objects.push_back(std::make_shared<Backboard>(
        Model("./src/assets/PinballTable3/Backboard.fbx"),
        std::make_shared<Shader>("./src/shaders/pinball/basic.vert",
                                 "./src/shaders/pinball/basic.frag"),
        Transformation(glm::vec3(10.0f, 10.0f, 10.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f)),
        ObjectType::STATIC));

    m_objects.push_back(std::make_shared<Ball>(
        Model("./src/assets/PinballTable3/ball2.fbx"),
        std::make_shared<Shader>("./src/shaders/ball/ball.vert", "./src/shaders/ball/ball.frag"),
        Transformation(glm::vec3(10.0f, 10.0f, 10.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 2.0f, 0.0f)),
        ObjectType::DYNAMIC, m_skybox));

    m_objects.push_back(std::make_shared<LeftWall>(
        Model("./src/assets/PinballTable3/Frame_Left.fbx"),
        std::make_shared<Shader>("./src/shaders/frame/frame.vert",
                                 "./src/shaders/frame/frame.frag"),
        Transformation(glm::vec3(10.0f, 10.0f, 10.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                       glm::vec3(2.075f, 0.125f, 0.0f)),
        ObjectType::STATIC, m_skybox));

    m_objects.push_back(std::make_shared<RightWall>(
        Model("./src/assets/PinballTable3/Frame_Right.fbx"),
        std::make_shared<Shader>("./src/shaders/frame/frame.vert",
                                 "./src/shaders/frame/frame.frag"),
        Transformation(glm::vec3(10.0f, 10.0f, 10.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                       glm::vec3(-2.075f, 0.125f, 0.0f)),
        ObjectType::STATIC, m_skybox));

    m_objects.push_back(std::make_shared<TopWall>(
        Model("./src/assets/PinballTable3/Frame_Top.fbx"),
        std::make_shared<Shader>("./src/shaders/frame/frame.vert",
                                 "./src/shaders/frame/frame.frag"),
        Transformation(glm::vec3(10.0f, 10.0f, 10.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 0.125f, 4.113f)),
        ObjectType::STATIC, m_skybox));

    m_objects.push_back(std::make_shared<BottomWall>(
        Model("./src/assets/PinballTable3/Frame_Bot.fbx"),
        std::make_shared<Shader>("./src/shaders/frame/frame.vert",
                                 "./src/shaders/frame/frame.frag"),
        Transformation(glm::vec3(10.0f, 10.0f, 10.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 0.125f, -4.113f)),
        ObjectType::STATIC, m_skybox));
}

void PinballScene::update(float dt) {
    for (auto& object : m_objects) {
        m_uGrid2D->clearCellsOfObject(object);
        object->update(dt, m_physics);
        m_uGrid2D->updateObjectMembership(object);
    }

    m_lightManager->updatePointLights(dt);
}

bool PinballScene::toggleLights() {
    m_drawLights = !m_drawLights;
    return m_drawLights;
}
bool PinballScene::toggleGrid() {
    m_drawGrid = !m_drawGrid;
    return m_drawGrid;
}
bool PinballScene::toggleBoundingBoxes() {
    m_drawBoundingBoxes = !m_drawBoundingBoxes;
    return m_drawBoundingBoxes;
}

void PinballScene::checkCollisions() {
    for (const auto& obj1 : m_objects) {
        if (obj1->type() != ObjectType::DYNAMIC) {
            continue;
        }
        for (const auto& cell : obj1->getCellMemberships()) {
            for (const auto& obj2 : cell->getMemberObjects()) {
                if (obj1 == obj2) {
                    continue;
                }
                collision::collide(obj1, obj2);
            }
        }
    }
}

void PinballScene::render() {
    m_bloomRenderer.bind();

    for (auto& object : m_objects) {
        object->draw(m_camera, m_lightManager);
        if (m_drawBoundingBoxes) {
            object->drawBoundingBox(m_camera);
        }
    }

    m_text->render();

    if (m_drawGrid) {
        m_uGrid2D->draw();
    }

    if (m_drawLights) {
        m_lightManager->drawPointLights();
    }

    // draw last
    m_skybox->draw();

    m_bloomRenderer.drawToBuffer();
}