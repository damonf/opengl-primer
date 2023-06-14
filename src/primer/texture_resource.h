#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

#include "gl_resource.h"

#include <glad/glad.h>

#include <stdexcept>

namespace primer {

     class TextureResource : public GLResource<1> {
     
         public: 
             TextureResource() : GLResource(glGenTextures, glDeleteTextures) {}
     
             void bind(GLenum target) {
                 glBindTexture(target, id(0));
             }
     };
     
}

#endif


