add_library(primer "")
add_subdirectory(primer)

include_directories(
  SYSTEM
  ${INCLUDE_BASE}
  )

add_custom_command(
    TARGET primer
    POST_BUILD
    COMMAND cp ${RESOURCE_BASE}/container.jpg ${CMAKE_BINARY_DIR}/apps/
    )
