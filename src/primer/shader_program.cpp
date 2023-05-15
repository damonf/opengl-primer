#include <glad/glad.h>

#include <stdexcept>
#include <array>

#include "shader.h"
#include "shader_program.h"

ShaderProgram::ShaderProgram(
    Shader<GL_VERTEX_SHADER>& vertex_shader,
    Shader<GL_FRAGMENT_SHADER>& fragment_shader
    )
{
    glAttachShader(id_, vertex_shader.get_id());
    glAttachShader(id_, fragment_shader.get_id());
    glLinkProgram(id_);

    check_compile_errors(id_);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
    :
      id_{other.id_}
{
    other.id_ = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
    delete_program();
    id_ = other.id_;
    other.id_ = 0;

    return *this;
}

ShaderProgram::~ShaderProgram() {
    delete_program();
}

void ShaderProgram::use() const {
    glUseProgram(id_);
}

GLint ShaderProgram::get_uniform_location(const std::string& name) const {

    const GLint loc = glGetUniformLocation(id_, "transform");

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
        const GLsizei max_length = 1024;
        std::array<GLchar, max_length> info_log{};

        glGetProgramInfoLog(shader, max_length, nullptr, info_log.data());

        std::stringstream message;

        message << "Shader program linking failed: "
                << info_log.data();

        throw std::runtime_error{message.str()};
    }
}

