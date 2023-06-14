#ifndef GL_RESOURCE_H
#define GL_RESOURCE_H

#include <glad/glad.h>

#include <array>
#include <algorithm>

namespace primer {

    template <GLsizei GLSIZEI>
    class GLResource {
        public:
            using allocater = void(*)(GLsizei, GLuint *);
            using deallocater = void(*)(GLsizei, const GLuint *);
    
            GLResource(
                    allocater allocate
                    , deallocater deallocate
                    )
                :
                    deallocate_(deallocate)
            {
                allocate(GLSIZEI, ids_.data());
            }
    
            virtual ~GLResource() = 0;
    
            GLResource(const GLResource&) = delete;
            GLResource& operator=(const GLResource&) = delete;
    
            GLResource(GLResource&& other) noexcept;
            GLResource& operator=(GLResource&& other) noexcept;
    
        protected:
           [[nodiscard]] GLuint id(GLsizei idx) const {
                return ids_.at(idx);
            }
    
        private:
            std::array<GLuint, GLSIZEI> ids_{};
            deallocater deallocate_{};
    };
    
    template <GLsizei GLSIZEI>
    inline GLResource<GLSIZEI>::~GLResource() {
    
        if (std::any_of(ids_.cbegin(), ids_.cend(),
                    [] (const auto& id) {
                        return id != 0;
                    })) {
            deallocate_(GLSIZEI, ids_.data());
        }
    }
    
    template <GLsizei GLSIZEI>
    inline GLResource<GLSIZEI>::GLResource(GLResource<GLSIZEI>&& other) noexcept
        :
        ids_(other.ids_)
    {
        std::fill_n(other.ids_.begin(), GLSIZEI, 0);
    }
    
    template <GLsizei GLSIZEI>
    inline GLResource<GLSIZEI>& GLResource<GLSIZEI>::operator=(
            GLResource<GLSIZEI>&& other
            ) noexcept {
    
        std::copy_n(other.ids_.cbegin(), GLSIZEI, ids_.begin());
        std::fill_n(other.ids_.begin(), GLSIZEI, 0);
        return *this;
    }

}

#endif
