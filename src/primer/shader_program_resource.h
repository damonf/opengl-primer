#ifndef SHADER_PROGRAM_RESOURCE_H
#define SHADER_PROGRAM_RESOURCE_H

#include "gl_single_resource.h"

namespace primer {

    class ShaderProgramResource : public GLSingleResource {
    
        public:
            ShaderProgramResource() : GLSingleResource(
                glCreateProgram
                , glDeleteProgram 
                )
            {}
    
            [[nodiscard]] GLuint get_id() const {
                return id();
            }
    };

}

#endif

