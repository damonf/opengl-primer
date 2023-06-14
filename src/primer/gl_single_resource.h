#ifndef GL_SINGLE_RESOURCE_H
#define GL_SINGLE_RESOURCE_H

#include <glad/glad.h>

#include <stdexcept>

namespace primer {

    class GLSingleResource {
        public:
            using allocater = GLuint(*)();
            using deallocater = void(*)(GLuint);
    
            GLSingleResource(
                    allocater allocate
                    , deallocater deallocate
                    )
                :
                    id_{allocate()}
                    , deallocate_(deallocate)
            {
            }
    
            virtual ~GLSingleResource() = 0;
    
            GLSingleResource(const GLSingleResource&) = delete;
            GLSingleResource& operator=(const GLSingleResource&) = delete;
    
            GLSingleResource(GLSingleResource&& other) noexcept;
            GLSingleResource& operator=(GLSingleResource&& other) noexcept;
    
        protected:
           [[nodiscard]] GLuint id() const {
                return id_;
            }
    
        private:
            GLuint id_{};
            deallocater deallocate_{};
    };
    
    inline GLSingleResource::~GLSingleResource() {
        if (id_ != 0) {
            deallocate_(id_);
        }
    }
    
    inline GLSingleResource::GLSingleResource(GLSingleResource&& other) noexcept
        :
        id_(other.id_)
    {
        other.id_ = 0;
    }
    
    inline GLSingleResource& GLSingleResource::operator=(
            GLSingleResource&& other
            ) noexcept {

        id_ = other.id_;
        other.id_ = 0;
    
        return *this;
    }

}

#endif

