cmake_minimum_required(VERSION 3.23)
project(voxerra)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
        src/core/main.cpp
        src/core/glad/glad.c
        src/core/VertexArray.cpp
        src/core/VertexBuffer.cpp
        src/core/ElementBuffer.cpp
        src/core/Shader.cpp
        src/core/Shader.cpp
        src/game/Camera.cpp src/game/Camera.h)

add_subdirectory(ext/glfw)

target_include_directories(${PROJECT_NAME} PUBLIC ext/glfw/include)
target_link_directories(${PROJECT_NAME} PRIVATE ext/glfw/src)

target_link_libraries(${PROJECT_NAME} glfw)

include_directories(${PROJECT_NAME} deps/include)

add_custom_target(shaders
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/core/shaders ${CMAKE_BINARY_DIR}/shaders
        COMMENT "copying ${CMAKE_SOURCE_DIR}/src/core/shaders to ${CMAKE_BINARY_DIR}/shaders"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

add_dependencies(voxerra shaders)
