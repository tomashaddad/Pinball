#pragma once

#include "SDLManager.h"
#include <memory>

class FPSTimer {
public:
	FPSTimer(std::shared_ptr<SDLManager> sdlManager);

	void start();
	void end();
	const float getAverageFPS();

private:
	const float getFPS();

private:
	std::shared_ptr<SDLManager> m_sdlManager;

	unsigned int m_start;
	unsigned int m_end;

	unsigned int m_counter;
	float m_runningFps;
	float m_averageFps;
};