#include "shader_program.h"

#include <glad/glad.h>

#include <stdexcept>
#include <array>

namespace primer {

    ShaderProgram::ShaderProgram(
        std::unique_ptr<ShaderProgramResource> shader_program_resource
        , std::unique_ptr<Shader<GL_VERTEX_SHADER>> vertex_shader
        , std::unique_ptr<Shader<GL_FRAGMENT_SHADER>> fragment_shader
        )
        :
            shader_program_resource_{std::move(shader_program_resource)}
    {
        auto id = shader_program_resource_->get_id();
        glAttachShader(id, vertex_shader->get_id());
        glAttachShader(id, fragment_shader->get_id());
        glLinkProgram(id);
    
        check_compile_errors(id);
    }
    
    void ShaderProgram::use() const {
        glUseProgram(shader_program_resource_->get_id());
    }
    
    GLint ShaderProgram::get_uniform_location(const std::string& name) const {
    
        const GLint loc = glGetUniformLocation(shader_program_resource_->get_id(), name.c_str());
    
        if (loc == -1) {
            throw std::runtime_error{name + " not a valid uniform variable"};
        }
    
        return loc;
    }
    
    void ShaderProgram::check_compile_errors(GLuint shader) {
        GLint success{0};
    
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
    
        if (success != GL_TRUE)
        {
            constexpr GLsizei max_length = 1024;
            std::array<GLchar, max_length> info_log{};
    
            glGetProgramInfoLog(shader, max_length, nullptr, info_log.data());
    
            std::stringstream message;
    
            message << "Shader program linking failed: "
                    << info_log.data();
    
            throw std::runtime_error{message.str()};
        }
    }

}
