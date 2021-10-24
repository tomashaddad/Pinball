#pragma once

#include <memory>

#include "Transformation.h"
#include "model/BoundingBox.h"
#include "model/Model.h"

class Collider {
public:
    Collider() = default;
    Collider(Model& model);
    void update(Transformation& transformation);

private:
    BoundingBox m_boundingBox;
};
