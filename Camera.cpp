#include "Camera.h"
#include <iostream>

// Standard camera settings
const glm::vec3 EYE_STD = glm::vec3(0, 0, 20);
const glm::vec3 CENTER_STD = glm::vec3(0);
const glm::vec3 UP_STD = glm::vec3(0, 1, 0);
const float FOVY_STD = 60;
const float NEAR_STD = 1;
const float FAR_STD = 1000;
const float EPSILON = 1e-4f;

Camera::Camera() {
    eye = EYE_STD;
    center = CENTER_STD;
    up = UP_STD;
    fovy = FOVY_STD;
    near = NEAR_STD;
    far = FAR_STD;
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up,
    float fovy, float near, float far) {
    this->eye = eye;
    this->center = center;
    this->up = up;
    this->fovy = fovy;
    this->near = near;
    this->far = far;
}

glm::vec3 Camera::getEye() const {
    return eye;
}

glm::vec3 Camera::getCenter() const {
    return center;
}

glm::vec3 Camera::getUp() const {
    return up;
}

glm::mat4 Camera::getViewMat() const {
    return glm::lookAt(eye, center, up);
}


glm::mat4 Camera::getProjMat(int width, int height) const {
    return glm::perspective(glm::radians(fovy), (float)width / (float)height,
        near, far);
}

void Camera::setEye(glm::vec3 eye) {
    fixCameraVecs(eye, center, up);
}

void Camera::setCenter(glm::vec3 center) {
    fixCameraVecs(eye, center, up);
}

void Camera::setUp(glm::vec3 up) {
    fixCameraVecs(eye, center, up);
}

void Camera::setCameraCoordSystem(glm::vec3 eye,
                                  glm::vec3 center, 
                                  glm::vec3 up) {
    fixCameraVecs(eye, center, up);

}

void Camera::fixCameraVecs(glm::vec3 eye, 
                           glm::vec3 center, 
                           glm::vec3 up) {
    glm::vec3 toCenter = normalize(eye - center);
    glm::vec3 right = glm::normalize(glm::cross(up, toCenter));
    up = glm::normalize(glm::cross(toCenter, right));

    float upLength = glm::length(up);
    if (upLength > 1 + EPSILON || upLength < 1 - EPSILON) {
        std::cout << "Error: Gimbal lock with new cam coordinate system!";
        std::cout << "Will not change camera coordinate system\n";
        return;
    }
    this->eye = eye;
    this->center = center;
    this->up = up;
}

