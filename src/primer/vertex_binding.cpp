#include "vertex_binding.h"

#include <glad/glad.h>

#include <stdexcept>
#include <memory>

namespace primer {

    VertexBinding::VertexBinding(
            std::unique_ptr<VertexArrayResource> vao
            ,std::unique_ptr<BufferResource> vbo
            )
        :
            vao_(std::move(vao))
            , vbo_(std::move(vbo))
    {
        vao_->bind();
        vbo_->bind(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_STATIC_DRAW);
    
        define_array(pos_loc_, pos_size_, pos_offset_);
        define_array(col_loc_, col_size_, col_offset_);
        define_array(tex_loc_, tex_size_, tex_offset_);
    
        // unbind 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    void VertexBinding::define_array(
            unsigned int location
            , int size
            , std::size_t offset
            ) {
    
        glVertexAttribPointer(
                location    // location (as specified in the vertex shader) 
                , size      // vertex size
                , GL_FLOAT  // data type
                , GL_FALSE  // normalise
                , stride_ * sizeof(float)
                , reinterpret_cast<const GLvoid *>(offset) //NOLINT
                );
    
        // enable the attribute (disabled by default)
        glEnableVertexAttribArray(location);
    }
    
    void VertexBinding::draw() {
    
        vao_->bind();
        
        glDrawArrays(
                GL_TRIANGLES
                , 0     // starting index of vertex array to draw
                , vertex_count()    // how many vertices to draw
                );
    }

}
