target_sources(primer
    PRIVATE
      glad.c
      stb_image.h
)


target_include_directories(primer
  SYSTEM
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )
 
