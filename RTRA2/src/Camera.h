#pragma once

// Dependencies
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>

#include "SDLManager.h"

enum class Axis { x, y, z };

enum class Direction { forward, backward };

class Camera {
public:
    Camera(std::shared_ptr<SDLManager> sdlManager);

    void moveForward(const float dt);
    void moveBackward(const float dt);
    void strafeLeft(const float dt);
    void strafeRight(const float dt);
    void yaw(signed int degree);
    void pitch(signed int degree);
    void rollLeft(const float dt);
    void rollRight(const float dt);

    void reset();

public:
    glm::vec3 getPosition() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    const float& getFOV() const;
    const float& getNearPlane() const;
    const float& getFarPlane() const;

    const glm::vec3 getForwardVector() const;

private:
    std::shared_ptr<SDLManager> m_sdlManager;

    float m_fov;
    float m_near;
    float m_far;

    glm::quat m_rotation;
    glm::vec3 m_position;

    const float m_movementSpeed;
    const float m_rotationSpeed;
    const float m_mouseSpeed;
};