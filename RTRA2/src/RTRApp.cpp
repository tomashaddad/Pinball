#include "RTRApp.h"

#include <iostream>

#include "scene/PinballScene.h"
#include "utility/FPSTimer.h"

RTRApp::RTRApp(const std::string& title, unsigned int width, unsigned int height, bool fullscreen)
    : m_state(State::GOOD)
    , m_sdlManager(std::make_shared<SDLManager>(title, width, height, fullscreen))
    , m_glManager(std::make_shared<GLManager>())
    , m_camera(std::make_shared<Camera>(m_sdlManager))
    , m_lightManager(std::make_shared<LightManager>(m_camera))
    , m_pinballScene(std::make_shared<PinballScene>(m_camera, m_lightManager))
    , m_fpsTimer(std::make_shared<FPSTimer>(m_sdlManager))
    , m_text(std::make_shared<Text>())
    , m_grid(m_camera, 12, 5, 0.5) {}

void RTRApp::run() {
    while (m_state != State::QUIT) {
        m_fpsTimer->start();

        float dt = m_sdlManager->getFrameDeltaTime();
        checkInput(dt);
        renderFrame(dt);

        m_sdlManager->swapBuffers();
        m_sdlManager->updateWindow();

        m_fpsTimer->end();
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
                    case SDLK_r:
                        m_camera->reset();
                        break;
                    case SDLK_ESCAPE:
                        m_state = State::QUIT;
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                m_camera->yaw(event.motion.xrel);
                m_camera->pitch(event.motion.yrel);
                break;
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_W]) {
        m_camera->moveForward(dt);
    }

    if (keystates[SDL_SCANCODE_A]) {
        m_camera->strafeLeft(dt);
    }

    if (keystates[SDL_SCANCODE_S]) {
        m_camera->moveBackward(dt);
    }

    if (keystates[SDL_SCANCODE_D]) {
        m_camera->strafeRight(dt);
    }

    if (keystates[SDL_SCANCODE_Q]) {
        m_camera->rollLeft(dt);
    }

    if (keystates[SDL_SCANCODE_E]) {
        m_camera->rollRight(dt);
    }
}

void RTRApp::renderFrame(float dt) {
    m_text->render();
    m_pinballScene->render();
    m_grid.draw();
}

void RTRApp::quit() {
    m_state = State::QUIT;
    gltTerminate();
}