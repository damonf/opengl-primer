#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
// #include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <array>

template <int SHADER_T>
class Shader
{
    public:
        Shader(const unsigned char* shader_resource, size_t length);

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        ~Shader() {
            delete_shader();
        }

        void delete_shader() {
            if (id_ != 0) {
                glDeleteShader(id_);
                id_ = 0;
            }
        }

        [[nodiscard]] GLuint get_id() const {
            return id_;
        }

    private:
        void check_compile_errors(GLuint shader);

    GLuint id_{glCreateShader(SHADER_T)};
};

template<int SHADER_T>
Shader<SHADER_T>::Shader(const unsigned char* shader_resource, size_t length) {

    const std::string shader_string(
        reinterpret_cast<const char* >(shader_resource)
      , length
        );

    const auto *shader_code = shader_string.c_str();

    glShaderSource(id_, 1, &shader_code, nullptr);
    glCompileShader(id_);
    check_compile_errors(id_);
}

template<int SHADER_T>
Shader<SHADER_T>::Shader(Shader&& other) noexcept
    :
      id_{other.id_}
{
    other.id_ = 0;
}

template<int SHADER_T>
Shader<SHADER_T>& Shader<SHADER_T>::operator=(Shader&& other) noexcept {
    delete_shader();
    id_ = other.id_;
    other.id_ = 0;

    return *this;
}

template<int SHADER_T>
void Shader<SHADER_T>::check_compile_errors(GLuint shader_id) {
    GLint success{0};

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE)
    {
        const GLsizei max_length = 1024;
        std::array<GLchar, max_length> info_log{};
        glGetShaderInfoLog(shader_id, max_length, nullptr, info_log.data());
    
        std::stringstream message;
            
        message << "Shader compilation failed: " 
                << info_log.data();

        throw std::runtime_error{message.str()};
    }
}

#endif // SHADER_H 
