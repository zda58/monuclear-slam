#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>
#include <glm/ext/quaternion_float.hpp>

class Camera {
public:
    Camera();
    glm::vec3& get_position() { return position; }
    glm::quat& get_orientation_quaternion() { return orientation_quaternion; }
    glm::mat4 get_view_matrix();
    void update_position(glm::vec3 velocity);
    void update_orientation(glm::vec3 euler_rotation);
private:
    glm::vec3 position;
    glm::quat orientation_quaternion;
};

#endif
