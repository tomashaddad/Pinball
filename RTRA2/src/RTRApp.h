#pragma once

#include <array>
#include <memory>
#include <string>

#include "Camera.h"
#include "GLManager.h"
#include "SDLManager.h"
#include "lights/LightManager.h"
#include "scene/PinballScene.h"
#include "utility/FPSTimer.h"
#include "utility/Text.h"

class Physics;

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
    bool m_frameByFrame;
    bool m_step;

    std::shared_ptr<SDLManager> m_sdlManager;
    std::shared_ptr<GLManager> m_glManager;
    std::shared_ptr<Physics> m_physics;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<LightManager> m_lightManager;
    std::shared_ptr<Text> m_text;
    std::shared_ptr<PinballScene> m_pinballScene;
    std::shared_ptr<FPSTimer> m_fpsTimer;
};