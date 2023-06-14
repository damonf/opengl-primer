#ifndef VERTEX_BINDING
#define VERTEX_BINDING

#include "vertex_array_resource.h"
#include "buffer_resource.h"

#include <array>
#include <memory>

namespace primer {

    class VertexBinding {
    
        public:
            VertexBinding(
                    std::unique_ptr<VertexArrayResource> vao
                    , std::unique_ptr<BufferResource> vbo
                    );
    
            void draw();
    
        private:
            static constexpr std::size_t vertex_count() {
                return vertices_.size() / stride_;
            }
    
            static void define_array(
                unsigned int location
                , int size
                , std::size_t offset
                );
    
            // A cube
            static constexpr unsigned int pos_loc_ = 0;
            static constexpr unsigned int col_loc_ = 1;
            static constexpr unsigned int tex_loc_ = 2;

            static constexpr unsigned int pos_size_ = 3;
            static constexpr unsigned int col_size_ = 3;
            static constexpr unsigned int tex_size_ = 2;

            static constexpr unsigned int pos_offset_ = 0;
            static constexpr unsigned int col_offset_ = 3 * sizeof(float);
            static constexpr unsigned int tex_offset_ = 6 * sizeof(float);

            static constexpr unsigned int stride_ = 8;

            static constexpr std::array<float, 288> vertices_ = {
    
                // positions           // colors           // texture coords
                -0.5F, -0.5F, -0.5F,   1.0F, 0.0F, 0.0F,   0.0F, 0.0F,
                 0.5F, -0.5F, -0.5F,   0.0F, 1.0F, 0.0F,   1.0F, 0.0F,
                 0.5F,  0.5F, -0.5F,   0.0F, 0.0F, 1.0F,   1.0F, 1.0F,
                 0.5F,  0.5F, -0.5F,   1.0F, 0.0F, 0.0F,   1.0F, 1.0F,
                -0.5F,  0.5F, -0.5F,   0.0F, 1.0F, 0.0F,   0.0F, 1.0F,
                -0.5F, -0.5F, -0.5F,   0.0F, 0.0F, 1.0F,   0.0F, 0.0F,
    
                -0.5F, -0.5F,  0.5F,   1.0F, 0.0F, 0.0F,   0.0F, 0.0F,
                 0.5F, -0.5F,  0.5F,   0.0F, 1.0F, 0.0F,   1.0F, 0.0F,
                 0.5F,  0.5F,  0.5F,   0.0F, 0.0F, 1.0F,   1.0F, 1.0F,
                 0.5F,  0.5F,  0.5F,   1.0F, 0.0F, 0.0F,   1.0F, 1.0F,
                -0.5F,  0.5F,  0.5F,   0.0F, 1.0F, 0.0F,   0.0F, 1.0F,
                -0.5F, -0.5F,  0.5F,   0.0F, 0.0F, 1.0F,   0.0F, 0.0F,
    
                -0.5F,  0.5F,  0.5F,   1.0F, 0.0F, 0.0F,   1.0F, 0.0F,
                -0.5F,  0.5F, -0.5F,   0.0F, 1.0F, 0.0F,   1.0F, 1.0F,
                -0.5F, -0.5F, -0.5F,   0.0F, 0.0F, 1.0F,   0.0F, 1.0F,
                -0.5F, -0.5F, -0.5F,   1.0F, 0.0F, 0.0F,   0.0F, 1.0F,
                -0.5F, -0.5F,  0.5F,   0.0F, 1.0F, 0.0F,   0.0F, 0.0F,
                -0.5F,  0.5F,  0.5F,   0.0F, 0.0F, 1.0F,   1.0F, 0.0F,
    
                 0.5F,  0.5F,  0.5F,   1.0F, 0.0F, 0.0F,   1.0F, 0.0F,
                 0.5F,  0.5F, -0.5F,   0.0F, 1.0F, 0.0F,   1.0F, 1.0F,
                 0.5F, -0.5F, -0.5F,   0.0F, 0.0F, 1.0F,   0.0F, 1.0F,
                 0.5F, -0.5F, -0.5F,   1.0F, 0.0F, 0.0F,   0.0F, 1.0F,
                 0.5F, -0.5F,  0.5F,   0.0F, 1.0F, 0.0F,   0.0F, 0.0F,
                 0.5F,  0.5F,  0.5F,   0.0F, 0.0F, 1.0F,   1.0F, 0.0F,
    
                -0.5F, -0.5F, -0.5F,   1.0F, 0.0F, 0.0F,   0.0F, 1.0F,
                 0.5F, -0.5F, -0.5F,   0.0F, 1.0F, 0.0F,   1.0F, 1.0F,
                 0.5F, -0.5F,  0.5F,   0.0F, 0.0F, 1.0F,   1.0F, 0.0F,
                 0.5F, -0.5F,  0.5F,   1.0F, 0.0F, 0.0F,   1.0F, 0.0F,
                -0.5F, -0.5F,  0.5F,   0.0F, 1.0F, 0.0F,   0.0F, 0.0F,
                -0.5F, -0.5F, -0.5F,   0.0F, 0.0F, 1.0F,   0.0F, 1.0F,
    
                -0.5F,  0.5F, -0.5F,   1.0F, 0.0F, 0.0F,   0.0F, 1.0F,
                 0.5F,  0.5F, -0.5F,   0.0F, 1.0F, 0.0F,   1.0F, 1.0F,
                 0.5F,  0.5F,  0.5F,   0.0F, 0.0F, 1.0F,   1.0F, 0.0F,
                 0.5F,  0.5F,  0.5F,   1.0F, 0.0F, 0.0F,   1.0F, 0.0F,
                -0.5F,  0.5F,  0.5F,   0.0F, 1.0F, 0.0F,   0.0F, 0.0F,
                -0.5F,  0.5F, -0.5F,   0.0F, 0.0F, 1.0F,   0.0F, 1.0F
            };
    
            std::unique_ptr<VertexArrayResource> vao_{};
            std::unique_ptr<BufferResource> vbo_{};
    };

}

#endif
