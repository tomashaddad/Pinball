#include "Sandbox.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "api/Shader.h"

Sandbox::Sandbox(std::shared_ptr<Camera> camera)
    : m_camera(camera)
    , m_bagShader("./src/shaders/scene00/model_loading/bag.vert",
                  "./src/shaders/scene00/model_loading/bag.frag")
    , m_bagModel("./src/assets/backpack/backpack.obj") {}

Sandbox::~Sandbox() { std::cout << "Scene00 destructor called!" << std::endl; }

void Sandbox::render() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = m_camera->getViewMatrix();
    glm::mat4 projection = m_camera->getProjectionMatrix();

    m_bagShader.bind();

    m_bagShader.setMat4("model", model);
    m_bagShader.setMat4("view", view);
    m_bagShader.setMat4("projection", projection);

    m_bagModel.draw(m_bagShader);
}