#include "PinballScene.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "api/Shader.h"

PinballScene::PinballScene(std::shared_ptr<Camera> camera)
    : m_camera(camera)
    , m_skybox(camera)
    , m_bagShader("./src/shaders/pinball/basic.vert", "./src/shaders/pinball/basic.frag")
    , m_ball("./src/assets/PinballTable3/Backboard.fbx")
    , m_lightManager(camera) {}

void PinballScene::render() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 projection = m_camera->getProjectionMatrix();

    m_bagShader.bind();

    m_bagShader.setMat4("model", model);
    m_bagShader.setMat4("view", view);
    m_bagShader.setMat4("projection", projection);
    m_bagShader.setVec3f("viewPos", m_camera->getPosition());
    m_bagShader.setDirectionalLight("directionalLight", m_lightManager.getDirectionalLight());
    m_bagShader.setInt("lightNumber", m_lightManager.sizeOfPointLights());

    for (int i = 0; i < m_lightManager.sizeOfPointLights(); ++i) {
        m_bagShader.setPointLight("pointLights", m_lightManager.getPointLights()[i], i);
    }

    m_ball.draw(m_bagShader);

    m_skybox.draw();
}