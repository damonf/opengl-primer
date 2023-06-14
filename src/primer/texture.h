#ifndef TEXTURE_H
#define TEXTURE_H

#include "texture_resource.h"

#include <string>
#include <memory>
#include <functional>

namespace primer {

    using image_free_func = void(*)(void*);
    using stbi_image_unique_ptr = std::unique_ptr<unsigned char, image_free_func>; 
    
    class Texture {
    
        public:
            Texture(
                    std::unique_ptr<TextureResource> texture
                    , const std::string& texture_file
                    );
    
            void bind(GLenum target) {
                texture_->bind(target);
            }
    
        private:
            stbi_image_unique_ptr load_image(const std::string& texture_file);
    
            std::unique_ptr<TextureResource> texture_{};
            int width_{0};
            int height_{0};
            int nrChannels_{0};
    };

}

#endif // TEXTURE_H

