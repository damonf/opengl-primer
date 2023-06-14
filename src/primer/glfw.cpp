#include "glfw.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <iostream>

namespace primer {

    Glfw::Glfw() {
        glfwSetErrorCallback([](int error, const char* description) {
                std::cerr << "Error " << error << ", " << description << std::endl;
            });
    
        if (glfwInit() == GLFW_FALSE) {
            throw std::domain_error("initializing GLFW failed");
        }
    
        is_init_ = true;
    }
    
    Glfw::~Glfw() {
        if (is_init_) {
            glfwTerminate();
            is_init_ = false;
        }
    }
    
    Glfw::Glfw(Glfw&& glfw) noexcept
        :
            is_init_{glfw.is_init_}
    {
        glfw.is_init_ = false;
    }
    
    Glfw& Glfw::operator=(Glfw&& glfw) noexcept {
        is_init_ = glfw.is_init_;
        glfw.is_init_ = false;
    
        return *this;
    }

}
