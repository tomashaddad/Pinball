#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Camera::Camera(std::shared_ptr<SDLManager> sdlManager)
    : m_sdlManager(sdlManager)

    , m_fov(45.0f)
    , m_near(0.1f)
    , m_far(100.0f)

    // start above and in front of the board, look at the centre
    //, m_startingPosition({0.0f, 8.0f, 8.0f})
    , m_startingPosition({0.0f, 8.0f, 0.2f})
    , m_currentPosition(m_startingPosition)
    , m_rotation({1.0f, 0.0f, 0.0f, 0.0f})

    , m_movementSpeed(3)
    , m_rotationSpeed(50)
    , m_mouseSpeed(0.001) {
    m_rotation = lookAt({0.0f, 0.0f, 0.0f});
}

void Camera::moveForward(float dt) {
    m_currentPosition += m_rotation * glm::vec3(0.0f, 0.0f, -m_movementSpeed * dt);
}

void Camera::moveBackward(float dt) {
    m_currentPosition += m_rotation * glm::vec3(0.0f, 0.0f, m_movementSpeed * dt);
}

void Camera::strafeLeft(float dt) {
    m_currentPosition += m_rotation * glm::vec3(-m_movementSpeed * dt, 0.0f, 0.0f);
}

void Camera::strafeRight(float dt) {
    m_currentPosition += m_rotation * glm::vec3(m_movementSpeed * dt, 0.0f, 0.0f);
}

void Camera::yaw(signed int degree) {
    m_rotation *= glm::angleAxis(-(float)degree * m_mouseSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::pitch(signed int degree) {
    m_rotation *= glm::angleAxis(-(float)degree * m_mouseSpeed, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::rollLeft(float dt) {
    m_rotation *= glm::angleAxis(glm::radians(m_rotationSpeed * dt), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::rollRight(float dt) {
    m_rotation *= glm::angleAxis(glm::radians(-m_rotationSpeed * dt), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::rise(float dt) {
    m_currentPosition += m_rotation * glm::vec3(0.0f, m_movementSpeed * dt, 0.0f);
}

void Camera::fall(float dt) {
    m_currentPosition += m_rotation * glm::vec3(0.0f, -m_movementSpeed * dt, 0.0f);
}

/*
    Technically this function is buggy; if the camera up vector and the direction vector
    are parallel, then everything gets wonky. I don't understand the math enough to know
    how to fix this elegantly! It works so long as we don't start somewhere on the y axis. :)
*/

glm::quat Camera::lookAt(glm::vec3 target) {
    glm::vec3 normalDirection = glm::normalize(target - m_currentPosition);
    glm::vec3 cameraUp = m_rotation * glm::vec3(0.0f, 1.0f, 0.0f);
    return glm::quatLookAt(normalDirection, cameraUp);
}

void Camera::reset() {
    m_currentPosition = m_startingPosition;
    m_rotation = glm::identity<glm::quat>();
    m_rotation = lookAt({0.0f, 0.0f, 0.0f});
}

glm::vec3 Camera::getPosition() const { return m_currentPosition; }

glm::mat4 Camera::getViewMatrix() const {
    auto mat4rotation = glm::toMat4(glm::inverse(m_rotation));
    auto translation = glm::translate(glm::mat4(1.0f), -m_currentPosition);
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