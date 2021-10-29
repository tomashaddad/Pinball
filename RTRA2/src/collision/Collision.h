#pragma once

#include <memory>

class Object;

namespace collision {
void collide(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2);
}