#include "Backboard.h"

#include "collision/Rectangular.h"
#include "model/Model.h"

Backboard::Backboard()
    : Object(Model("./src/assets/PinballTable3/Backboard.fbx"),
             {"./src/shaders/pinball/basic.vert", "./src/shaders/pinball/basic.frag"},
             Rectangular()) {
    m_transformation.setScaling({
        10.0f,
        10.0f,
        10.0f,
    });
}

void Backboard::draw(std::shared_ptr<Camera> camera, std::shared_ptr<LightManager> lightManager) {
    glm::mat4 model = m_transformation.getModelMatrix();
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();

    m_shader.bind();

    m_shader.setMat4("model", model);
    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);
    m_shader.setVec3f("viewPos", camera->getPosition());
    m_shader.setDirectionalLight("directionalLight", lightManager->getDirectionalLight());
    m_shader.setInt("lightNumber", lightManager->sizeOfPointLights());

    for (int i = 0; i < lightManager->sizeOfPointLights(); ++i) {
        m_shader.setPointLight("pointLights", lightManager->getPointLights()[i], i);
    }

    m_model.draw(m_shader);
}