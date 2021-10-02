#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Camera.h"
#include "api/Shader.h"
#include "glad/glad.h"

class Skybox {
public:
    Skybox(std::shared_ptr<Camera> camera);

    void draw();

private:
    GLuint loadSkybox(std::vector<std::string> faces);

    std::shared_ptr<Camera> m_camera;
    Shader m_shader;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_skyboxTexture;
};
