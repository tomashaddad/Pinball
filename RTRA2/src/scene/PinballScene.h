#pragma once
#include <memory>
#include <vector>

class Physics;
class Skybox;
class Object;
class LightManager;
class Camera;
class UGrid2D;
class Text;

#include "BloomRenderer.h"

class PinballScene {
public:
    PinballScene(std::shared_ptr<Camera> camera, std::shared_ptr<LightManager> lightManager,
                 std::shared_ptr<Physics> physics, std::shared_ptr<Text> text);
    void update(float dt);
    void checkCollisions();
    void render();

    bool toggleLights();
    bool toggleGrid();
    bool toggleBoundingBoxes();

private:
    bool m_drawLights;
    bool m_drawGrid;
    bool m_drawBoundingBoxes;

    std::vector<std::shared_ptr<Object>> m_objects;

    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<LightManager> m_lightManager;
    std::shared_ptr<UGrid2D> m_uGrid2D;
    std::shared_ptr<Skybox> m_skybox;
    std::shared_ptr<Physics> m_physics;
    std::shared_ptr<Text> m_text;

    BloomRenderer m_bloomRenderer;
};