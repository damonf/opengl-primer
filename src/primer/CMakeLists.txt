target_sources(primer
    PRIVATE
      build_primer.cpp
      primer.cpp
      shader_program.cpp
      texture.cpp
      stb_image.cpp
      camera.cpp
      vertex_binding.cpp
      glfw.cpp
      glfw_window.cpp
)

add_subdirectory(shaders)
add_subdirectory(third_party)

find_package(OpenGL REQUIRED)

set(all_libs 
   "-lglfw"
   "-lX11"
   "-lpthread"
   "-lXrandr"
   "-lXi"
   "-ldl"
   )

target_include_directories(primer PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${INCLUDE_BASE}
  )
 
target_link_libraries(primer
  ${all_libs}
  OpenGL::GL
  )

#message(STATUS "all_libs = ${all_libs}")
