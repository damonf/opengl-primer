#ifndef GLFW_H
#define GLFW_H

namespace primer {

    class Glfw {
        public:
            Glfw();
            ~Glfw();
    
            Glfw(const Glfw&) = delete;
            Glfw& operator=(const Glfw&) = delete;
    
            Glfw(Glfw&& glfw) noexcept;
            Glfw& operator=(Glfw&& glfw) noexcept;
    
        private:
            bool is_init_{};
    };

}

#endif // GLFW_H
