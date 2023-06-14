#ifndef SHADER_RESOURCE_H
#define SHADER_RESOURCE_H

#include "gl_single_resource.h"

namespace primer {
    
    template<GLenum SHADER_T>
    class ShaderResource : public GLSingleResource {
    
        public:
            ShaderResource() : GLSingleResource(
                []() { return glCreateShader(SHADER_T); }
                , glDeleteShader 
                )
            {}
    
            [[nodiscard]] GLuint get_id() const {
                return id();
            }
    };

}

#endif
