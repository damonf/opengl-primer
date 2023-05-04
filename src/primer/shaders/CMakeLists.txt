embed_resource("vertex_shader.glsl" "vertex_shader.h" "VERTEX_SHADER")
embed_resource("fragment_shader.glsl" "fragment_shader.h" "FRAGMENT_SHADER")

target_sources(primer
  PRIVATE
  fragment_shader.h
  vertex_shader.h
  )

target_include_directories(primer
  SYSTEM
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )
