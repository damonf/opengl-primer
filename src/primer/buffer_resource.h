#ifndef BUFFER_RESOURCE_H
#define BUFFER_RESOURCE_H

#include "gl_resource.h"

#include <glad/glad.h>

#include <stdexcept>

namespace primer {

    class BufferResource : public GLResource<1> {
    
        public: 
            BufferResource() : GLResource(glGenBuffers, glDeleteBuffers) {}
    
            void bind(GLenum target) {
                glBindBuffer(target, id(0));
            }
    };

}

#endif

