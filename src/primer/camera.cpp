#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace primer {

    Camera::Camera(
        const glm::vec3& position
        )
        :
        position_{position}
    {
        update_camera_vectors();
    }
    
    glm::mat4 Camera::get_view_matrix() {
        return glm::lookAt(position_, position_ + front_, up_);
    }
    
    void Camera::move(CameraMovement direction, float delta) {
        auto velocity = movement_speed_ * delta;
    
        if (direction == CameraMovement::forward) {
            position_ += front_ * velocity;
        }
    
        if (direction == CameraMovement::backward) {
            position_ -= front_ * velocity;
        }
        
        if (direction == CameraMovement::left) {
            position_ -= right_ * velocity;
        }
    
        if (direction == CameraMovement::right) {
            position_ += right_ * velocity;
        }
    }
    
    void Camera::rotate(Yaw yaw_adjust, Pitch pitch_adjust) {
        yaw_   += yaw_adjust * mouse_sensitivity_;
        pitch_ += pitch_adjust * mouse_sensitivity_;
    
        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch_ > max_pitch_) {
            pitch_ = max_pitch_;
        }
    
        if (pitch_ < min_pitch_) {
            pitch_ = min_pitch_;
        }
    
        update_camera_vectors();
    }
    
    void Camera::update_camera_vectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        // NOLINTBEGIN(cppcoreguidelines-pro-type-union-access) 
        front.x = std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
        front.y = std::sin(glm::radians(pitch_));
        front.z = std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
        // NOLINTEND(cppcoreguidelines-pro-type-union-access) 
        front_ = glm::normalize(front);
    
        // also re-calculate the Right and Up vector
        // normalize the vectors, because their length gets closer
        // to 0 the more you look up or down which results in slower movement.
        right_ = glm::normalize(glm::cross(front_, world_up_));  
        up_    = glm::normalize(glm::cross(right_, front_));
    }

}
