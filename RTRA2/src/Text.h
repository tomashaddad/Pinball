#pragma once

#include <string>

#include <glad/glad.h>
#define GLT_IMPLEMENTATION
#include "dependencies/gltext.h"

class Text
{
public:
	Text();
	~Text();
	void render() const;
	void toggleFPSMode();
private:

	void update() const;

	GLTtext* m_text;
	bool m_fpsMode;
	float m_xpos;
	float m_ypos;
	float m_size;
};