target_sources(primer
    PRIVATE
      glad.c
      primer.cpp
      shader_program.cpp
)

add_subdirectory(shaders)

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

message(STATUS "all_libs = ${all_libs}")
