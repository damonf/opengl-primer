#include "glfw_window.h"

namespace primer {

    GlfwWindow::GlfwWindow(std::unique_ptr<Glfw> glfw)
        :
            glfw_(std::move(glfw))
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
        window_ = glfw_window(
                glfwCreateWindow(
                    SCR_WIDTH
                    , SCR_HEIGHT
                    , "OpenGL-Primer"
                    , nullptr
                    , nullptr
                    )
                , glfwDestroyWindow
                );
    
        if (!window_)
        {
            throw std::domain_error(
                    "creating OpenGL window and context failed"
                    );
        }
    
        glfwMakeContextCurrent(window_.get());
    
        glfwSetFramebufferSizeCallback(
                window_.get()
                , []([[maybe_unused]] GLFWwindow* window, int width, int height)
                    {
                        // make sure the viewport matches the new window dimensions; note that width and 
                        // height will be significantly larger than specified on retina displays.
                        glViewport(0, 0, width, height);
                    } 
                );
    
        // glad: load all OpenGL function pointers
        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) //NOLINT
        {
            throw std::domain_error("failed to initialize OpenGL context");
        }
    
        // tell GLFW to capture our mouse
        glfwSetInputMode(window_.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    
    bool GlfwWindow::get_should_close() {
        return glfwWindowShouldClose(window_.get()) != 0;
    }
    
    void GlfwWindow::set_should_close(int val) {
        glfwSetWindowShouldClose(window_.get(), val);
    }
    
    void GlfwWindow::swap_buffers() {
        glfwSwapBuffers(window_.get());
    }
    
    std::pair<int, int> GlfwWindow::get_frame_buffer_size() {
    
        int width{};
        int height{};
    
        glfwGetFramebufferSize(window_.get(), &width, &height);
    
        return std::make_pair(width, height);
    }
    
    std::pair<double, double> GlfwWindow::get_curser_pos() {
    
        double xpos_in{};
        double ypos_in{};
    
        glfwGetCursorPos(window_.get(), &xpos_in, &ypos_in);
    
        return std::make_pair(xpos_in, ypos_in);
    }
    
    int GlfwWindow::get_key(int key) {
        return glfwGetKey(window_.get(), key);
    }
 
}
