#include "Text.h"

#include <iostream>
#include <sstream>

Text::Text()
    : m_draw(true)
    , m_frameByFrame(true)
    , m_lights(false)
    , m_grid(false)
    , m_boundingBoxes(false)
    , m_xpos(20.0f)
    , m_ypos(20.0f)
    , m_size(2.0f)
    , m_fps(0) {
    gltInit();
    m_text = gltCreateText();
}

void Text::update() const {
    std::stringstream text;

    // clang-format off

    text << "FPS: " << m_fps << std::endl
         << "Frame by frame: " << (m_frameByFrame ? "ON" : "OFF") << std::endl
         << "Lights: " << (m_lights ? "ON" : "OFF") << std::endl
         << "Grid: " << (m_grid ? "ON" : "OFF") << std::endl
         << "Bounding Boxes: " << (m_boundingBoxes ? "ON" : "OFF") << std::endl;

    // clang-format on
    gltSetText(m_text, text.str().c_str());
}

Text::~Text() {
    gltDeleteText(m_text);
    gltTerminate();
}

void Text::render() const {
    update();

    if (m_draw) {
        gltBeginDraw();
        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        gltDrawText2D(m_text, m_xpos, m_ypos, m_size);
        gltEndDraw();
    }
}

void Text::toggleDraw() { m_draw = !m_draw; }
void Text::fps(float fps) { m_fps = fps; }
void Text::setLights(bool lights) { m_lights = lights; }
void Text::setGrid(bool grid) { m_grid = grid; }
void Text::setBoundingBoxes(bool boundingBoxes) { m_boundingBoxes = boundingBoxes; }
void Text::setFrameByFrame(bool frameByFrame) { m_frameByFrame = frameByFrame; }