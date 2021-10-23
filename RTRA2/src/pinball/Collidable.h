#pragma once

#include <memory>

#include "textures/Model.h"

class Collidable {
public:
    Collidable();

private:
    std::unique_ptr<Model> m_model;
};
