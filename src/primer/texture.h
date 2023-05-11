#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <memory>
#include <functional>

using image_free_func = void(*)(void*);
using stbi_image_unique_ptr = std::unique_ptr<unsigned char, image_free_func>; 

class Texture {
    public:
        Texture(const std::string& texture_file);

        stbi_image_unique_ptr load_image(const std::string& texture_file);

        [[nodiscard]] unsigned int get_id() const {
            return id_;
        }

    private:
        unsigned int id_{0};
        int width_{0};
        int height_{0};
        int nrChannels_{0};
};

#endif // TEXTURE_H

