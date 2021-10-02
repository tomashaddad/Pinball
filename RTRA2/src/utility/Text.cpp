#include "Text.h"

#include <iostream>
#include <sstream>

Text::Text()
    : m_fpsMode(false)
    , m_xpos(20.0f)
    , m_ypos(20.0f)
    , m_size(2.0f) {
    gltInit();
    m_text = gltCreateText();
}

void Text::update() const {
    std::stringstream text("Wow!");

    gltSetText(m_text, text.str().c_str());
}

Text::~Text() {
    gltDeleteText(m_text);
    gltTerminate();
}

void Text::render() const {
    update();

    gltBeginDraw();
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);
    gltDrawText2D(m_text, m_xpos, m_ypos, m_size);
    gltEndDraw();
}

void Text::toggleFPSMode() { m_fpsMode = !m_fpsMode; }