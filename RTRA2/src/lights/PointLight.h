#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "objects/Transformation.h"

class Camera;
class Shader;

class PointLight {
public:
    PointLight(std::shared_ptr<Shader> shader, glm::vec3 ambient, glm::vec3 diffuse,
               glm::vec3 specular, float radius, float constant, float linear, float quadratic,
               double sideLength);

    void draw(std::shared_ptr<Camera> camera);
    void update(double dt);

    // GLM's random functions didn't work for me!
    glm::vec3 getRandomUnit();

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;

private:
    std::shared_ptr<Shader> m_shader;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::uvec3> m_indices;

    Transformation m_transformation;

    glm::vec3 m_rotationAxis;
    float m_angle;

    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_IBO;

    double m_sideLength;
};
