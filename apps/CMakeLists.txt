
add_executable(primer-app
  "main.cpp"
  )

#include_directories(
    #"${INCLUDE_BASE}"
    #)

#find_package(Boost 1.79 COMPONENTS program_options REQUIRED)

include_directories(
  SYSTEM
  ${INCLUDE_BASE}
  )

target_link_libraries(primer-app PRIVATE primer)

#message(STATUS "BUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}")
