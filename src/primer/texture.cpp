#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "stb_image.h"

#include <string>
#include <stdexcept>
#include <memory>

Texture::Texture(const std::string& texture_file) {

    auto data = load_image(texture_file);

    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_); 

    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // tell stb_image.h to flip loaded texture's on the y-axis.
    //stbi_set_flip_vertically_on_load(true);

    glTexImage2D(
            GL_TEXTURE_2D
            , 0
            , GL_RGB
            , width_
            , height_
            , 0
            , GL_RGB
            , GL_UNSIGNED_BYTE
            , data.get()
            );

    glGenerateMipmap(GL_TEXTURE_2D);
}

stbi_image_unique_ptr Texture::load_image(const  std::string& texture_file) { 

    stbi_image_unique_ptr data(
            stbi_load(
                texture_file.c_str()
                , &width_
                , &height_
                , &nrChannels_
                , 0
            )
            , stbi_image_free
            );

    if (!data) {
        throw std::domain_error(
                std::string{"Failed to load texture: "} + texture_file
                );
    }

    return data;
}
