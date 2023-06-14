#ifndef PRIMER_H
#define PRIMER_H

#include "camera.h"
#include "vertex_binding.h"
#include "glfw_window.h"
#include "texture.h"
#include "shader_program.h"

#include <memory>

namespace primer {

    class Primer {
        public:
            Primer(
                    std::unique_ptr<GlfwWindow> glfw_window
                    , std::unique_ptr<VertexBinding> vertex_binding
                    , std::unique_ptr<ShaderProgram> shader_program
                    , std::unique_ptr<Texture> texture
                    , std::unique_ptr<FrameDelta> frame_delta
                    , std::unique_ptr<Camera> camera
                    );
    
            void run();
    
        private:
            void process_input();
            void process_mouse();
    
            std::unique_ptr<GlfwWindow> glfw_window_;
            std::unique_ptr<VertexBinding> vertex_binding_;
            std::unique_ptr<ShaderProgram> shader_program_;
            std::unique_ptr<Texture> texture_;
            std::unique_ptr<FrameDelta> frame_delta_;
            std::unique_ptr<Camera> camera_;
    
            bool init_mouse_{true};
            float last_x_{};
            float last_y_{};
    };

}

#endif // PRIMER_H
