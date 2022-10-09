cmake_minimum_required(VERSION 3.23)
project(voxerra)

set(CMAKE_CXX_STANDARD 23)

# get core source files
set(CORE
        dependencies/source/glad/glad.c
        source/main.cpp
        source/core/VertexArray.cpp
        source/core/VertexBuffer.cpp
        source/core/ElementBuffer.cpp
        source/core/Shader.cpp
        source/core/Shader.cpp
        source/core/debuggui/DebugGui.cpp source/core/FrameBuffer.cpp source/core/FrameBuffer.h)

# get game source files
set(GAME
        source/game/Camera.cpp)

# get util source files
set(UTILS
        dependencies/source/imgui/imgui.cpp
        dependencies/source/imgui/imgui_demo.cpp
        dependencies/source/imgui/imgui_draw.cpp
        dependencies/source/imgui/imgui_tables.cpp
        dependencies/source/imgui/imgui_widgets.cpp
        dependencies/source/imgui/imgui_impl_glfw.cpp
        dependencies/source/imgui/imgui_impl_opengl3.cpp)

# get compiled libraries files
set(LIBS
        ${CMAKE_SOURCE_DIR}/dependencies/binaries/libglfw3.a)

# link all source files
add_executable(${PROJECT_NAME}
        ${CORE}
        ${GAME}
        ${UTILS})

# link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})

# include files
include_directories(${PROJECT_NAME} dependencies/include)
include_directories(${PROJECT_NAME} dependencies/include/imgui)

# copy shaders to output directory
add_custom_target(copy_shaders
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/source/core/shaders ${CMAKE_BINARY_DIR}/shaders
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_dependencies(voxerra copy_shaders)
