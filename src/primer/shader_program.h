#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.h"
#include "shader_program_resource.h"

#include <memory>

namespace primer {

    class ShaderProgram
    {
        public:
            ShaderProgram(
                std::unique_ptr<ShaderProgramResource> shader_program_resource
                , std::unique_ptr<Shader<GL_VERTEX_SHADER>> vertex_shader
                , std::unique_ptr<Shader<GL_FRAGMENT_SHADER>> fragment_shader
                );
    
            [[nodiscard]] GLuint id() const {
                return shader_program_resource_->get_id();
            }
    
            void use() const;
            [[nodiscard]] GLint get_uniform_location(const std::string& name) const;
    
        private:
            static void check_compile_errors(GLuint shader);
    
            std::unique_ptr<ShaderProgramResource> shader_program_resource_;
    };

}

#endif // SHADER_PROGRAM_H
