#include "collision.h"

#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <typeinfo>

#include "objects/Object.h"
#include "objects/table/Backboard.h"
#include "objects/table/Ball.h"

bool collision::collide(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2) {
    if (!boundingBoxesCollide(obj1, obj2)) {
        return false;
    }

    std::string obj1Type = typeid(*obj1.get()).name();
    std::string obj2Type = typeid(*obj2.get()).name();

    // only balls and paddles are dynamic objects that will ever make it here

    bool colliding = false;

    if (obj1Type == "class Ball") {
        auto ball = std::dynamic_pointer_cast<Ball>(obj1);
        if (obj2Type == "class Backboard") {
            auto backboard = std::dynamic_pointer_cast<Backboard>(obj2);
            colliding = check(ball, backboard);
            if (colliding) {
                resolve(ball, backboard);
            }
        }
    } else if (obj1Type == "class Paddle") {
        // do stuff
    } else {
        std::cout << "Something went wrong if you are here!";
        std::cout << "(obj1: " << obj1Type << ", obj2: " << obj2 << ")" << std::endl;
    }

    return colliding;
}

bool collision::boundingBoxesCollide(std::shared_ptr<Object> obj1, std::shared_ptr<Object> obj2) {
    glm::vec3 aMin = obj1->getBoundingBox().getMin();
    glm::vec3 aMax = obj1->getBoundingBox().getMax();
    glm::vec3 bMin = obj2->getBoundingBox().getMin();
    glm::vec3 bMax = obj2->getBoundingBox().getMax();

    return (aMin.x <= bMax.x && aMax.x >= bMin.x) && (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
           (aMin.z <= bMax.z && aMax.z >= bMin.z);
}

bool collision::check(std::shared_ptr<Ball> ball, std::shared_ptr<Backboard> backboard) {
    glm::vec3 ballPos = ball->getPosition();
    float radius = ball->getRadius();

    glm::vec3 boardMin = backboard->getBoundingBox().getMin();
    glm::vec3 boardMax = backboard->getBoundingBox().getMax();

    return sphereBox(ballPos, radius, boardMin, boardMax);
}

void collision::resolve(std::shared_ptr<Ball> ball, std::shared_ptr<Backboard> backboard) {
    ball->bounce(1.0f);
}

bool collision::sphereBox(glm::vec3 spherePos, float sphereRadius, glm::vec3 boxMin,
                          glm::vec3 boxMax) {
    double x = glm::max(boxMin.x, glm::min(spherePos.x, boxMax.x));
    double y = glm::max(boxMin.y, glm::min(spherePos.y, boxMax.y));
    double z = glm::max(boxMin.z, glm::min(spherePos.z, boxMax.z));

    // this is the same as isPointInsideSphere
    double distance =
        glm::sqrt((x - spherePos.x) * (x - spherePos.x) + (y - spherePos.y) * (y - spherePos.y) +
                  (z - spherePos.z) * (z - spherePos.z));

    return distance < sphereRadius;
}