#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include "glfw.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

namespace primer {

    class GlfwWindow {
    
        using destroy_window = void(*)(GLFWwindow*);
        using glfw_window = std::unique_ptr<GLFWwindow, destroy_window>; 
    
        public:
            explicit GlfwWindow(std::unique_ptr<Glfw> glfw);
    
            bool get_should_close();
            void set_should_close(int val);
            void swap_buffers();
            std::pair<int, int> get_frame_buffer_size();
            std::pair<double, double> get_curser_pos();
            int get_key(int key);
    
        private:
            std::unique_ptr<Glfw> glfw_{};
            glfw_window window_{nullptr, nullptr};
    
            static constexpr unsigned int SCR_WIDTH = 800;
            static constexpr unsigned int SCR_HEIGHT = 600;
    };

}

#endif // GLFW_WINDOW_H
