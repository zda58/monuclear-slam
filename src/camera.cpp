#include "camera.h"
#include <iostream>
#include <glm/gtc/quaternion.hpp>

Camera::Camera() {
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->orientation_quaternion = glm::angleAxis(glm::radians(0.0f), glm::vec3(0, 0, 1));
}

glm::mat4 Camera::get_view_matrix() {
    glm::mat4 rotation_matrix = glm::mat4_cast(this->orientation_quaternion);
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), -this->position);
    glm::mat4 view_matrix = rotation_matrix * translation_matrix;
    return view_matrix;
}

void Camera::update_position(glm::vec3 velocity) {
    this->position += velocity;
}

void Camera::update_orientation(glm::vec3 euler_rotation) {
    if (euler_rotation.x == 0 && euler_rotation.y == 0 && euler_rotation.z == 0) {
        return;
    }
    
    glm::quat pitch_quat = glm::angleAxis(glm::radians(euler_rotation.x), glm::vec3(1, 0, 0));
    glm::quat yaw_quat = glm::angleAxis(glm::radians(euler_rotation.y), glm::vec3(0, 1, 0));

    this->orientation_quaternion = pitch_quat * this->orientation_quaternion * yaw_quat;
    
    glm::vec3 eulerAngles = glm::degrees(glm::eulerAngles(this->orientation_quaternion));
    std::cout << "Camera Euler Angles (Degrees): (" << eulerAngles.x << ", " << eulerAngles.y << ", " << eulerAngles.z << ")" << std::endl;

}