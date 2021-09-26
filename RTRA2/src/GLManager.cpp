#include "GLManager.h"

#include <iostream>


GLManager::GLManager()
    : m_depthTesting(true)
    , m_cullBackFace(true)
{
    // non-changing state
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // changing state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GLManager::toggleDepthTesting() {
    if (m_depthTesting) {
        glDisable(GL_DEPTH_TEST);
        m_depthTesting = false;
    } else {
        glEnable(GL_DEPTH_TEST);
        m_depthTesting = true;
    }
}

void GLManager::toggleBackFaceCulling() {
    if (m_cullBackFace) {
        glDisable(GL_CULL_FACE);
        m_cullBackFace = false;
    } else {
        glEnable(GL_CULL_FACE);
        m_cullBackFace = true;
    }
}

const bool GLManager::isDepthTesting() const {
    return m_depthTesting;
}

const bool GLManager::isCullingBackFaces() const {
    return m_cullBackFace;
}