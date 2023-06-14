#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace primer {

    class FrameDelta {
    public:
        void update_delta() {
            const auto current_frame = static_cast<float>(glfwGetTime());
            delta_time_ = current_frame - last_frame_;
            last_frame_ = current_frame;
        }
    
        [[nodiscard]] float get_delta() const {
            return delta_time_;
        }
    
    private:
        float delta_time_{0.0F}; // Time between current frame and last frame
        float last_frame_{0.0F}; // Time of last frame
    };

}
