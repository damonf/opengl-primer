#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vertex_shader.h"
#include "fragment_shader.h"
#include "shader.h"
#include "shader_program.h"
#include "texture.h"

#include <iostream>
#include <array>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int primer_main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) //NOLINT
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    Shader<GL_VERTEX_SHADER> vertex_shader{
        (const unsigned char*)VERTEX_SHADER
      , sizeof(VERTEX_SHADER)
    };

    Shader<GL_FRAGMENT_SHADER> fragment_shader{
        (const unsigned char*)FRAGMENT_SHADER
      , sizeof(FRAGMENT_SHADER)
    };

    const ShaderProgram shader_program{vertex_shader, fragment_shader};

    // A cube, 36 vertices (6 faces * 2 triangles * 3 vertices each)
    std::array<float, 288> vertices = {

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

    unsigned int VBO = 0;
    unsigned int VAO = 0;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)
            , (void*)nullptr);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float)
            , (void *)(3 * sizeof(float)) //NOLINT
            );
    glEnableVertexAttribArray(1);

    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float)
            , (void *)(6 * sizeof(float)) //NOLINT
            );
    glEnableVertexAttribArray(2);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    const Texture texture{"container.jpg"};

    shader_program.use(); // don't forget to activate/use the shader before setting uniforms! 

    glUniform1i(
            shader_program.get_uniform_location("texture1")
            , 0
            );

    // render loop
    // -----------
    while (glfwWindowShouldClose(window) == 0)
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.get_id());

        shader_program.use();

        // create transformations
        glm::mat4 model      = glm::mat4(1.0F); // make sure to initialize matrix to identity matrix first
        glm::mat4 view       = glm::mat4(1.0F);
        glm::mat4 projection = glm::mat4(1.0F);

        model      = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0F), glm::vec3(0.5F, 1.0F, 0.0F));
        view       = glm::translate(view, glm::vec3(0.0F, 0.0F, -3.0F));
        projection = glm::perspective(glm::radians(45.0F), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1F, 100.0F);

        // Set uniforms
        glUniformMatrix4fv(
                shader_program.get_uniform_location("model")
                , 1
                , GL_FALSE
                , glm::value_ptr(model)
                );

        glUniformMatrix4fv(
                shader_program.get_uniform_location("view")
                , 1
                , GL_FALSE
                , glm::value_ptr(view)
                );

        glUniformMatrix4fv(
                shader_program.get_uniform_location("projection")
                , 1
                , GL_FALSE
                , glm::value_ptr(projection)
                );

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window, int width, int height) // NOLINT
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

