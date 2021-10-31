#include "PointLight.h"

#include <glad/glad.h>

#include <cmath>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <random>

#include "api/Shader.h"

PointLight::PointLight(std::shared_ptr<Shader> shader, glm::vec3 ambient, glm::vec3 diffuse,
                       glm::vec3 specular, float radius, float constant, float linear,
                       float quadratic, double sideLength)
    : m_VAO(0)
    , m_VBO(0)
    , m_IBO(0)
    , m_shader(shader)
    , ambient(ambient)
    , diffuse(diffuse)
    , specular(specular)
    , position(getRandomUnit() * radius)
    , m_rotationAxis(glm::cross(glm::normalize(position), glm::normalize(getRandomUnit())))
    , m_angle(20.0f)
    , constant(constant)
    , linear(linear)
    , quadratic(quadratic)
    , m_sideLength(sideLength) {
    m_transformation.m_translation = position;
    double halfSideLength = sideLength / 2.0;
    glm::vec3 min = glm::vec3(-halfSideLength, -halfSideLength, -halfSideLength);
    glm::vec3 max = -1.0f * min;

    // clang-format off

    m_vertices.insert(m_vertices.end(), {
        // front
        {min.x, min.y, max.z},
        {max.x, min.y, max.z},
        {max.x, max.y, max.z},
        {min.x, max.y, max.z},
        // back
        {min.x, min.y, min.z},
        {max.x, min.y, min.z},
        {max.x, max.y, min.z},
        {min.x, max.y, min.z}
    });

    // vertices for a cube of triangles
    m_indices.insert(m_indices.end(), {
		{0, 1, 2}, {2, 3, 0}, // front
		{1, 5, 6}, {6, 2, 1}, // right
		{7, 6, 5}, {5, 4, 7}, // back
		{4, 0, 3}, {3, 7, 4}, // left
		{4, 5, 1}, {1, 0, 4}, // bottom
		{3, 2, 6}, {6, 7, 3}  // top
    });

    // clang-format on

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3),
                 glm::value_ptr(m_vertices[0]), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(glm::uvec3),
                 glm::value_ptr(m_indices[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

glm::vec3 PointLight::getRandomUnit() {
    std::random_device engine;

    std::uniform_real_distribution<float> thetaDist =
        std::uniform_real_distribution<float>{0.0f, 360.0f};
    std::uniform_real_distribution<float> phiDist =
        std::uniform_real_distribution<float>{-180.0f, 180.0f};

    float theta = thetaDist(engine);
    float phi = phiDist(engine);

    float pi = std::acos(-1);
    theta *= pi / 180.0;
    phi *= pi / 180.0;

    float x = cos(phi) * cos(theta);
    float y = cos(phi) * sin(theta);
    float z = sin(phi);

    return glm::vec3(x, y, z);
}

void PointLight::update(double dt) {
    m_transformation.m_rotation =
        glm::angleAxis(glm::radians(1.0f), glm::normalize(m_rotationAxis)) *
        m_transformation.m_rotation;

    m_transformation.m_translation =
        glm::vec3(glm::toMat4(glm::angleAxis(glm::radians(m_angle * (float)dt),
                                             glm::normalize(m_rotationAxis))) *
                  glm::vec4(m_transformation.m_translation, 1.0f));

    position = m_transformation.m_translation;
}

void PointLight::draw(std::shared_ptr<Camera> camera) {
    m_shader->bind();
    m_shader->setMat4("model", m_transformation.getModelMatrix());
    m_shader->setMat4("view", camera->getViewMatrix());
    m_shader->setMat4("projection", camera->getProjectionMatrix());

    m_shader->setPointLight("pointLights", *this);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size() * sizeof(glm::uvec3), GL_UNSIGNED_INT, 0);
}