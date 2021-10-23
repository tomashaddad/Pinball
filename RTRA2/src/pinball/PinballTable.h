#pragma once

#include <memory>
#include <vector>

#include "Cylindrical.h"
#include "Rectangular.h"
#include "Triangular.h"

class PinballTable {
public:
    PinballTable();
    void draw();

private:
    std::vector<std::shared_ptr<Collidable>> m_everything;
    Collidable m_backboard;
};
