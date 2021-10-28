#pragma once

#include <array>
#include <memory>
#include <string>

#include "Camera.h"
#include "GLManager.h"
#include "LightManager.h"
#include "SDLManager.h"
#include "scene/PinballScene.h"
#include "utility/FPSTimer.h"
#include "utility/Text.h"

enum class State {
    GOOD,
    RUN,
    QUIT,
};

class RTRApp {
public:
    RTRApp(const std::string& title, unsigned int width = 1920, unsigned int height = 1080,
           bool fullscreen = false);

    void run();

    void checkInput(float dt);
    void update(float dt);
    void renderFrame(float dt);
    void quit();

private:
    State m_state;

    std::shared_ptr<SDLManager> m_sdlManager;
    std::shared_ptr<GLManager> m_glManager;
    std::shared_ptr<Camera> m_camera;              // depends on SDLManager
    std::shared_ptr<LightManager> m_lightManager;  // depends on Camera
    std::shared_ptr<PinballScene> m_pinballScene;  // depends on LightManager, Camera
    std::shared_ptr<FPSTimer> m_fpsTimer;          // depends on SDLManager
    std::shared_ptr<Text> m_text;
};