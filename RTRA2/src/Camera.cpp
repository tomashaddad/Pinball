#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(std::shared_ptr<SDLManager> sdlManager)
    : m_sdlManager(sdlManager)
    , m_fov(45.0f)
    , m_near(0.1f)
    , m_far(100.0f)
    , m_position(glm::vec3(0.0f))
    , m_rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
    , m_movementSpeed(3)
    , m_rotationSpeed(50)
    , m_mouseSpeed(0.001) {}

void Camera::moveForward(const float dt) {
    m_position += m_rotation * glm::vec3(0.0f, 0.0f, -m_movementSpeed * dt);
}

void Camera::moveBackward(const float dt) {
    m_position += m_rotation * glm::vec3(0.0f, 0.0f, m_movementSpeed * dt);
}

void Camera::strafeLeft(const float dt) {
    m_position += m_rotation * glm::vec3(-m_movementSpeed * dt, 0.0f, 0.0f);
}

void Camera::strafeRight(const float dt) {
    m_position += m_rotation * glm::vec3(m_movementSpeed * dt, 0.0f, 0.0f);
}

void Camera::yaw(signed int degree) {
    m_rotation *= glm::angleAxis(-(float)degree * m_mouseSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::pitch(signed int degree) {
    m_rotation *= glm::angleAxis(-(float)degree * m_mouseSpeed, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::rollLeft(const float dt) {
    m_rotation *= glm::angleAxis(glm::radians(m_rotationSpeed * dt), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::rollRight(const float dt) {
    m_rotation *= glm::angleAxis(glm::radians(-m_rotationSpeed * dt), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::reset() {
    m_position = glm::vec3(0.0f);
    m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

glm::vec3 Camera::getPosition() const { return m_position; }

glm::mat4 Camera::getViewMatrix() const {
    auto mat4rotation = glm::toMat4(glm::inverse(m_rotation));
    auto translation = glm::translate(glm::mat4(1.0f), -m_position);
    return mat4rotation * translation;
}

glm::mat4 Camera::getProjectionMatrix() const {
    float width = static_cast<float>(m_sdlManager->getWindowWidth());
    float height = static_cast<float>(m_sdlManager->getWindowHeight());
    return glm::perspective(glm::radians(m_fov), width / height, m_near, m_far);
}

const float& Camera::getFOV() const { return m_fov; }

const float& Camera::getNearPlane() const { return m_near; }

const float& Camera::getFarPlane() const { return m_far; }

const glm::vec3 Camera::getForwardVector() const { return m_rotation * glm::vec3(0.0, 0.0, -1.0); }