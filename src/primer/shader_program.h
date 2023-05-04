#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.h"

class ShaderProgram
{
    public:
        ShaderProgram(
            Shader<GL_VERTEX_SHADER>& vertex_shader,
            Shader<GL_FRAGMENT_SHADER>& fragment_shader
            );

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&& other) noexcept;

        ~ShaderProgram();

        void delete_program() {
            if (id_ != 0) {
                glDeleteProgram(id_);
                id_ = 0;
            }
        }

        [[nodiscard]] GLuint id() const { return id_; }
        void use() const;

        void set_uniform(const std::string &name, float value) const;

    private:
        static void check_compile_errors(GLuint shader);

        GLuint id_{glCreateProgram()};
};


#endif // SHADER_PROGRAM_H
