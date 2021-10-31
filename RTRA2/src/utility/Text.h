#pragma once

#include <glad/glad.h>

#include <string>
#define GLT_IMPLEMENTATION
#include "dependencies/gltext.h"

class Text {
public:
    Text();
    ~Text();
    void render() const;
    void toggleDraw();

    void fps(float fps);

    void setLights(bool lights);
    void setGrid(bool grid);
    void setBoundingBoxes(bool boundingBoxes);
    void setFrameByFrame(bool frameByFrame);

private:
    void update() const;

    GLTtext* m_text;
    float m_fps;
    float m_xpos;
    float m_ypos;
    float m_size;

    bool m_lights;
    bool m_grid;
    bool m_boundingBoxes;
    bool m_draw;
    bool m_frameByFrame;
};