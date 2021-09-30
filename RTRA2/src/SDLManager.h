#pragma once

#include <SDL2/SDL.h>

#include <string>

struct DeltaTimer {
    float currentTime = 0;
    float lastTime = 0;
    float deltaTime = 0;
};

struct Window {
    const std::string title;
    int width;
    int height;
    bool fullscreen;
};

struct SDL {
    SDL_Window* window;
    SDL_GLContext context;
};

class SDLManager {
public:
    SDLManager(const std::string& title, int width, int height, bool fullscreen);
    ~SDLManager();
    bool initialise();
    void swapBuffers() const;
    void updateWindow();

public:
    const float getTimeElapsed();
    const float getFrameDeltaTime();

    const unsigned int getWindowWidth() const;
    const unsigned int getWindowHeight() const;

    const unsigned int getRefreshRate() const;

    const unsigned int getPerformanceCounter() const;
    const unsigned int getPerformanceFrequency() const;

private:
    bool initSDL();
    bool initWindow();
    bool initContext();
    bool initGLAD();

private:
    Window m_window;
    DeltaTimer m_deltaTimer;
    SDL m_sdl;
};
