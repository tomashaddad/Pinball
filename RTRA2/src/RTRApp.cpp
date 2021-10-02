#include "RTRApp.h"

#include <iostream>

#include "scene/Pinball.h"
#include "scene/Sandbox.h"
#include "utility/FPSTimer.h"

RTRApp::RTRApp(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
    : m_state(State::GOOD)
    , m_currentSceneNumber(0)
    , m_sdlManager(std::make_shared<SDLManager>(title, width, height, fullscreen))
    , m_glManager(std::make_shared<GLManager>())
    , m_camera(std::make_shared<Camera>(m_sdlManager))
    , m_currentScene(std::make_shared<Sandbox>(m_camera))
    , m_fpsTimer(std::make_shared<FPSTimer>(m_sdlManager))
    , m_text(std::make_shared<Text>()) {}

void RTRApp::run() {
    while (m_state != State::QUIT) {
        getFPSTimer()->start();

        float dt = getSDLManager()->getFrameDeltaTime();
        checkInput(dt);
        renderFrame(dt);

        getSDLManager()->swapBuffers();
        getSDLManager()->updateWindow();

        getFPSTimer()->end();
    }
}

void RTRApp::checkInput(float dt) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_state = State::QUIT;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_0:
                        switchToScene(0);
                        break;
                    case SDLK_1:
                        switchToScene(1);
                        break;
                    case SDLK_r:
                        getCamera()->reset();
                        break;
                    case SDLK_ESCAPE:
                        m_state = State::QUIT;
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                getCamera()->yaw(event.motion.xrel);
                getCamera()->pitch(event.motion.yrel);
                break;
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_W]) {
        getCamera()->moveForward(dt);
    }

    if (keystates[SDL_SCANCODE_A]) {
        getCamera()->strafeLeft(dt);
    }

    if (keystates[SDL_SCANCODE_S]) {
        getCamera()->moveBackward(dt);
    }

    if (keystates[SDL_SCANCODE_D]) {
        getCamera()->strafeRight(dt);
    }

    if (keystates[SDL_SCANCODE_Q]) {
        getCamera()->rollLeft(dt);
    }

    if (keystates[SDL_SCANCODE_E]) {
        getCamera()->rollRight(dt);
    }
}

void RTRApp::switchToScene(unsigned int sceneNumber) {
    if (m_currentSceneNumber == sceneNumber) {
        return;
    }

    switch (sceneNumber) {
        case 0:
            m_currentScene = std::make_unique<Sandbox>(m_camera);
            break;
        case 1:
            m_currentScene = std::make_unique<Pinball>(m_camera);
            break;
    }

    m_currentSceneNumber = sceneNumber;
}

void RTRApp::renderFrame(float dt) {
    m_text->render();
    m_currentScene->render();
}

void RTRApp::quit() {
    m_state = State::QUIT;
    gltTerminate();
}

SDLManager* RTRApp::getSDLManager() const { return m_sdlManager.get(); }

GLManager* RTRApp::getGLManager() const { return m_glManager.get(); }

Camera* RTRApp::getCamera() const { return m_camera.get(); }

SceneBase* RTRApp::getScene() const { return m_currentScene.get(); }

Text* RTRApp::getText() const { return m_text.get(); }

FPSTimer* RTRApp::getFPSTimer() const { return m_fpsTimer.get(); }

const unsigned int RTRApp::getCurrentSceneNumber() const { return m_currentSceneNumber; }