#ifndef CAMERA_H
#define CAMERA_H

#include "frame_delta.h"
#include <glm/glm.hpp>
#include <memory>

namespace primer {

    enum class CameraMovement {
        forward,
        backward,
        left,
        right
    };
    
    struct Yaw {
        const float value; // NOLINT
        constexpr operator float() const { return value; }
    };
    
    struct Pitch {
        const float value; // NOLINT
        constexpr operator float() const { return value; }
    };
    
    class Camera {

    public:
        explicit Camera(
            const glm::vec3& position
            );
    
        glm::mat4 get_view_matrix();
        void move(CameraMovement direction, float delta);
        void rotate(Yaw yaw_adjust, Pitch pitch_adjust);
    
    private:
        void update_camera_vectors();
    
        // Default camera values
        static constexpr auto default_yaw_         = -90.0F;
        static constexpr auto default_pitch_       =  0.0F;
        static constexpr auto default_speed_       =  2.5F;
        static constexpr auto default_sensitivity_ =  0.1F;

        static constexpr auto max_pitch_ = 89.0F;
        static constexpr auto min_pitch_ = -89.0F;

        // camera attributes
        glm::vec3 position_;
        glm::vec3 world_up_{glm::vec3(0.0F, 1.0F, 0.0F)};
        glm::vec3 front_{glm::vec3(0.0F, 0.0F, -1.0F)};
        glm::vec3 right_{glm::normalize(glm::cross(front_, world_up_))};
        glm::vec3 up_{glm::normalize(glm::cross(right_, front_))};
    
        // euler angles
        float yaw_{default_yaw_};
        float pitch_{default_pitch_};
    
        // camera options
        float movement_speed_{default_speed_};
        float mouse_sensitivity_{default_sensitivity_};
    };

}

#endif
