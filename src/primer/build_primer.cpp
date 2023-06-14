#include "build_primer.h"
#include "primer.h"
#include "vertex_binding.h"
#include "glfw_window.h"
#include "texture_resource.h"
#include "texture.h"
#include "shader.h"
#include "shader_program.h"
#include "vertex_shader.h"
#include "fragment_shader.h"
#include "buffer_resource.h"

#include <stdexcept>
#include <iostream>
#include <utility>

namespace primer {

    constexpr auto cube_texture{"container.jpg"};
    constexpr auto init_camera_pos = glm::vec3(0.0F, 0.0F,  3.0F);

    namespace {
        std::unique_ptr<GlfwWindow> make_glfw_window() {
            return std::make_unique<GlfwWindow>(
                    std::make_unique<Glfw>()
                    );
        };
    
        std::unique_ptr<VertexBinding> make_vertex_binding() {
            return std::make_unique<VertexBinding>(
                    std::make_unique<VertexArrayResource>()
                    , std::make_unique<BufferResource>()
                    );
        }
    
        std::unique_ptr<ShaderProgram> make_shader_program() {
    
            auto vertex_shader =
                std::make_unique<Shader<GL_VERTEX_SHADER>>(
                        std::make_unique<ShaderResource<GL_VERTEX_SHADER>>()
                        , (const unsigned char*)VERTEX_SHADER
                        , sizeof(VERTEX_SHADER)
                        );
        
            auto fragment_shader =
                std::make_unique<Shader<GL_FRAGMENT_SHADER>>(
                        std::make_unique<ShaderResource<GL_FRAGMENT_SHADER>>()
                        , (const unsigned char*)FRAGMENT_SHADER
                        , sizeof(FRAGMENT_SHADER)
                        );
        
            return std::make_unique<ShaderProgram>(
                    std::make_unique<ShaderProgramResource>()
                    , std::move(vertex_shader)
                    , std::move(fragment_shader)
                    );
        }
    
        std::unique_ptr<Texture> make_texture() {
     
            return std::make_unique<Texture>(
                    std::make_unique<TextureResource>()
                    , cube_texture
                    );
        }
    }

    Primer build_primer() {

        Primer primer{
            make_glfw_window()
            , make_vertex_binding()
            , make_shader_program()
            , make_texture()
            , std::make_unique<FrameDelta>()
            , std::make_unique<Camera>(init_camera_pos)
        };
    
        return primer;
    }

}
