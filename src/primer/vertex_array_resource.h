#ifndef VERTEX_ARRAY_RESOURCE_H
#define VERTEX_ARRAY_RESOURCE_H

#include "gl_resource.h"

#include <glad/glad.h>

#include <stdexcept>

namespace primer {

    class VertexArrayResource : public GLResource<1> {
        public:
            VertexArrayResource() : GLResource(glGenVertexArrays, glDeleteVertexArrays) {}
    
            void bind() {
                glBindVertexArray(id(0));
            }
    };

}

#endif
