cmake_minimum_required(VERSION 3.16)
project(graphite LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

# Paths for external dependencies
set(GLFW_PATH "external/glfw")
set(GLAD_PATH "external/glad")
set(GLM_PATH  "external/glm")

# --- GLFW ---
add_subdirectory(${GLFW_PATH})
# GLFW provides its own target: glfw

# --- GLAD ---
add_library(glad STATIC "${GLAD_PATH}/src/glad.c")
target_include_directories(glad PUBLIC "${GLAD_PATH}/include")

# --- OpenGL ---
find_package(OpenGL REQUIRED)

# --- Sources ---
file(GLOB_RECURSE SOURCES
        "src/*.c"
        "src/*.cpp"
)
file(GLOB_RECURSE HEADERS
        "src/*.h"
        "src/*.hpp"
)

# --- Example Executable ---
add_executable(graphite ${SOURCES} ${HEADERS})
# add_library(graphite STATIC ${SOURCES} ${HEADERS})

include_directories(src/includes)

# Link libraries to the example executable
target_link_libraries(graphite
        PRIVATE
        glfw                   # GLFW target
        glad                   # GLAD library
        ${OPENGL_LIBRARIES}    # OpenGL
)

# Include directories for the executable (only needed for GLM)
target_include_directories(graphite PRIVATE ${GLM_PATH})

# --- Platform-Specific Configuration ---
if (UNIX)
    find_package(X11 REQUIRED)
    target_link_libraries(graphite PRIVATE ${X11_LIBRARIES})
    message(STATUS "X11 libraries added")
endif()
