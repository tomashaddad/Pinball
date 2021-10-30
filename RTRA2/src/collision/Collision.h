#pragma once

#include <memory>
class Object;
class Ball;
class Backboard;

#include "model/BoundingBox.h"

namespace collision {
bool collide(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2);
bool boundingBoxesCollide(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2);

bool check(std::shared_ptr<Ball> ball, std::shared_ptr<Backboard> backboard);
void resolve(std::shared_ptr<Ball> ball, std::shared_ptr<Backboard> backboard);

bool sphereBox(glm::vec3 spherePos, float sphereRadius, glm::vec3 rectMin, glm::vec3 rectMax);
};  // namespace collision
