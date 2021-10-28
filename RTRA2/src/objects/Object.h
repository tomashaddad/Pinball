#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Camera.h"
#include "LightManager.h"
#include "Transformation.h"
#include "api/Shader.h"
#include "collision/Collider.h"
#include "model/BoundingBox.h"
#include "model/Model.h"

class GridCell;
class UGrid2D;

enum class ObjectShape { RECTANGULAR, TRIANGULAR, SPHERICAL, CYLINDRICAL };

class Object {
public:
    Object(std::string modelPath, std::shared_ptr<Shader> shader);

    virtual void draw(std::shared_ptr<Camera> camera,
                      std::shared_ptr<LightManager> lightManager) = 0;

    void update(float dt);

    void drawBoundingBox(std::shared_ptr<Camera> camera);
    BoundingBox getBoundingBox();

protected:
    std::vector<std::shared_ptr<GridCell>> m_cellMemberships;

    Transformation m_transformation;
    Model m_model;
    Collider m_collider;
    BoundingBox m_boundingBox;
    std::shared_ptr<Shader> m_shader;
};
