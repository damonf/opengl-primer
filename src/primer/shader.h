#ifndef SHADER_H
#define SHADER_H

#include "shader_resource.h"

#include <glad/glad.h>
// #include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <array>
#include <memory>

namespace primer {

    template <GLenum SHADER_T>
    class Shader
    {
        public:
            Shader(
                    std::unique_ptr<ShaderResource<SHADER_T>> shader_resource
                    , const unsigned char* shader_code
                    , size_t length
                    );
    
            [[nodiscard]] GLuint get_id() const {
                return shader_resource_->get_id();
            }
    
        private:
            void check_compile_errors(GLuint shader);
    
            std::unique_ptr<ShaderResource<SHADER_T>> shader_resource_;
    };
    
    template<GLenum SHADER_T>
    Shader<SHADER_T>::Shader(
            std::unique_ptr<ShaderResource<SHADER_T>> shader_resource
            , const unsigned char* shader_code
            , size_t length
            ) 
        :
            shader_resource_{std::move(shader_resource)}
    {
    
        const std::string shader_string(
            reinterpret_cast<const char*>(shader_code)
          , length
            );
    
        const auto *shader = shader_string.c_str();
    
        auto id = shader_resource_->get_id();
        glShaderSource(id, 1, &shader, nullptr);
        glCompileShader(id);
        check_compile_errors(id);
    }
    
    template<GLenum SHADER_T>
    void Shader<SHADER_T>::check_compile_errors(GLuint shader_id) {
        GLint success{0};
    
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    
        if (success != GL_TRUE)
        {
            constexpr GLsizei max_length = 1024;
            std::array<GLchar, max_length> info_log{};
            glGetShaderInfoLog(shader_id, max_length, nullptr, info_log.data());
        
            std::stringstream message;
                
            message << "Shader compilation failed: " 
                    << info_log.data();
    
            throw std::runtime_error{message.str()};
        }
    }

}

#endif // SHADER_H 
