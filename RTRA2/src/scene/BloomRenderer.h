#pragma once

#include <memory>
#include <vector>

class Shader;

class BloomRenderer {
public:
    BloomRenderer(std::shared_ptr<Shader> blur, std::shared_ptr<Shader> combine);

    void bind();
    void drawToBuffer();
    void renderQuad();

private:
    std::shared_ptr<Shader> m_blurShader;
    std::shared_ptr<Shader> m_combineShader;

    unsigned int m_colourBuffers[2];
    unsigned int m_pingPongFBO[2];
    unsigned int m_pingPongColourBuffers[2];

    unsigned int m_quadVAO;
    unsigned int m_quadVBO;
    unsigned int m_FBO;
    unsigned int m_RBO;
};
