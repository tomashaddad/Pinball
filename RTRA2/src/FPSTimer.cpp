#pragma once

#include "FPSTimer.h"

FPSTimer::FPSTimer(std::shared_ptr<SDLManager> sdlManager)
	: m_sdlManager(sdlManager)
	, m_start(0)
	, m_end(0)
	, m_counter(0)
	, m_runningFps(0)
	, m_averageFps(0) {}

void FPSTimer::start() {
	++m_counter;
	m_start = m_sdlManager->getPerformanceCounter();
}

void FPSTimer::end() {
	m_end = m_sdlManager->getPerformanceCounter();
	m_runningFps += getFPS();
	if (m_counter == 100) {
		m_averageFps = m_runningFps / 100;
		m_counter = 0;
		m_runningFps = 0;
	}
}

const float FPSTimer::getFPS() {
	return 1.0f / ((m_end - m_start) / static_cast<float>(m_sdlManager->getPerformanceFrequency()));
}

const float FPSTimer::getAverageFPS() {
	return m_averageFps;
}