cmake_minimum_required(VERSION 3.16)

project(
    OpenGLPrimer
    VERSION 1.0
    DESCRIPTION "OpenGL primer"
    LANGUAGES C CXX
    )

include(cmake/EmbedResource.cmake)

# generate the test target
enable_testing()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
  -Wall
  -Wextra
  -Wwrite-strings
  -Wno-parentheses
  -Wno-comment
  -Wpedantic
  -Warray-bounds
  -Weffc++
  #-Werror
  )

# run clang-tidy
set(CMAKE_CXX_CLANG_TIDY 
  clang-tidy;
  -checks=-concurrency-mt-unsafe,-readability-identifier-length; 
  -header-filter=${CMAKE_CURRENT_SOURCE_DIR};
  #-warnings-as-errors=*;
  )

set(INCLUDE_BASE
    "${PROJECT_SOURCE_DIR}/include")

set(RESOURCE_BASE
    "${PROJECT_SOURCE_DIR}/resources")

add_subdirectory(apps)
add_subdirectory(src)
#add_subdirectory(tests)

# install(TARGETS main_app DESTINATION "${PROJECT_SOURCE_DIR}/bin/")
