#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "Transformation.h"
#include "model/Model.h"
#include "objects/BoundingBox.h"

class GridCell;
class UGrid2D;
class Physics;
class Camera;
class LightManager;
class Shader;

enum class ObjectType { STATIC, DYNAMIC };
enum class ObjectShape { RECTANGULAR, TRIANGULAR, SPHERICAL, CYLINDRICAL };

class Object {
public:
    Object(Model model, std::shared_ptr<Shader> shader, Transformation transformation,
           ObjectType type);

    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) = 0;
    virtual void update(float dt, std::shared_ptr<Physics> physics);

    void add(std::shared_ptr<GridCell> cell);
    bool has(std::shared_ptr<GridCell> cell);
    void remove(std::shared_ptr<GridCell> cell);

    ObjectType type();

    std::vector<std::shared_ptr<GridCell>> getCellMemberships();

    void drawBoundingBox(std::shared_ptr<Camera> camera);
    BoundingBox getBoundingBox();
    glm::vec3 getPosition();

protected:
    std::vector<std::shared_ptr<GridCell>> m_cellMemberships;

    ObjectType m_type;
    Transformation m_transformation;
    Model m_model;
    BoundingBox m_boundingBox;
    std::shared_ptr<Shader> m_shader;
};
