#include "primer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_program.h"
#include "texture.h"
#include "frame_delta.h"
#include "vertex_binding.h"

#include <array>
#include <utility>

namespace primer {

    Primer::Primer(
            std::unique_ptr<GlfwWindow> glfw_window
            , std::unique_ptr<VertexBinding> vertex_binding
            , std::unique_ptr<ShaderProgram> shader_program
            , std::unique_ptr<Texture> texture
            , std::unique_ptr<FrameDelta> frame_delta
            , std::unique_ptr<Camera> camera
            ) 
        :
        glfw_window_{std::move(glfw_window)}
        , vertex_binding_{std::move(vertex_binding)}
        , shader_program_{std::move(shader_program)}
        , texture_{std::move(texture)}
        , frame_delta_{std::move(frame_delta)}
        , camera_{std::move(camera)}
    {
        glEnable(GL_DEPTH_TEST);
    }
    
    void Primer::run() {
    
        shader_program_->use();
    
        glUniform1i(
                shader_program_->get_uniform_location("texture1")
                , 0
                );
    
        auto [scr_width, scr_height] = glfw_window_->get_frame_buffer_size();
    
        glm::mat4 projection =
            glm::perspective(
                    glm::radians(45.0F)
                    , (float)scr_width / (float)scr_height
                    , 0.1F
                    , 100.0F
                    );
    
        glUniformMatrix4fv(
                shader_program_->get_uniform_location("projection")
                , 1
                , GL_FALSE
                , glm::value_ptr(projection)
                );
    
        // render loop
        while (!glfw_window_->get_should_close())
        {
            process_input();
            process_mouse();
    
            glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
            glActiveTexture(GL_TEXTURE0);
            texture_->bind(GL_TEXTURE_2D);
    
            shader_program_->use();
    
            frame_delta_->update_delta();
            auto view = camera_->get_view_matrix();
    
            glUniformMatrix4fv(
                    shader_program_->get_uniform_location("view")
                    , 1
                    , GL_FALSE
                    , glm::value_ptr(view)
                    );
    
            glm::mat4 model = glm::mat4(1.0F);
            model = glm::rotate(
                    model
                    , (float)glfwGetTime() * glm::radians(50.0F)
                    , glm::vec3(0.5F, 1.0F, 0.0F)
                    );
    
            glUniformMatrix4fv(
                    shader_program_->get_uniform_location("model")
                    , 1
                    , GL_FALSE
                    , glm::value_ptr(model)
                    );
    
            vertex_binding_->draw();
    
            glfw_window_->swap_buffers();
            glfwPollEvents();
        }
    }
    
    void Primer::process_mouse() {
    
        auto [xpos_in, ypos_in] = glfw_window_->get_curser_pos();
    
        const auto xpos = static_cast<float>(xpos_in);
        const auto ypos = static_cast<float>(ypos_in);
    
        if (init_mouse_) {
    
            if (last_x_ == xpos && last_y_ == ypos) {
                init_mouse_ = false;
            }
    
            last_x_ = xpos;
            last_y_ = ypos;
    
            return;
        }
    
        const auto xoffset = xpos - last_x_;
        const auto yoffset = last_y_ - ypos; // reversed since y-coordinates go from bottom to top
        last_x_ = xpos;
        last_y_ = ypos;
    
        camera_->rotate(Yaw{xoffset}, Pitch{yoffset});
    }
    
    void Primer::process_input()
    {
        if (glfw_window_->get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfw_window_->set_should_close(GLFW_TRUE);
        }
    
        if (glfw_window_->get_key(GLFW_KEY_W) == GLFW_PRESS) {
            camera_->move(
                    CameraMovement::forward
                    , frame_delta_->get_delta()
                    );
        }
    
        if (glfw_window_->get_key(GLFW_KEY_S) == GLFW_PRESS) {
            camera_->move(
                    CameraMovement::backward
                    , frame_delta_->get_delta()
                    );
        }
    
        if (glfw_window_->get_key(GLFW_KEY_A) == GLFW_PRESS) {
            camera_->move(
                    CameraMovement::left
                    , frame_delta_->get_delta()
                    );
        }
    
        if (glfw_window_->get_key(GLFW_KEY_D) == GLFW_PRESS) {
            camera_->move(
                    CameraMovement::right
                    , frame_delta_->get_delta()
                    );
        }
    }

}
