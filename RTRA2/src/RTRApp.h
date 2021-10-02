#pragma once

#include <array>
#include <memory>
#include <string>

#include "Camera.h"
#include "GLManager.h"
#include "SDLManager.h"
#include "scene/SceneBase.h"
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
    void switchToScene(unsigned int sceneNumber);
    void renderFrame(float dt);
    void quit();

public:
    SDLManager* getSDLManager() const;
    GLManager* getGLManager() const;
    Camera* getCamera() const;
    SceneBase* getScene() const;
    Text* getText() const;
    FPSTimer* getFPSTimer() const;

    const unsigned int getCurrentSceneNumber() const;

private:
    State m_state;
    unsigned int m_currentSceneNumber;

    std::shared_ptr<SDLManager> m_sdlManager;
    std::shared_ptr<GLManager> m_glManager;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<SceneBase> m_currentScene;
    std::shared_ptr<Text> m_text;
    std::shared_ptr<FPSTimer> m_fpsTimer;
};