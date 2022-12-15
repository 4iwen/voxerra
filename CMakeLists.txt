cmake_minimum_required(VERSION 3.23)
project(voxerra)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")

# get core source files
set(CORE
        dependencies/source/glad/glad.c
        source/main.cpp
        source/core/vertexarray/vertexarray.cpp
        source/core/vertexbuffer/vertexbuffer.cpp
        source/core/elementbuffer/elementbuffer.cpp
        source/core/shader/shader.cpp
        source/core/shader/shader.cpp
        source/core/gui/gui.cpp
        source/core/utils/utils.cpp
        source/core/application/application.cpp
        source/core/window/window.cpp)

# get game source files
set(GAME
        source/game/camera/camera.cpp
        source/game/worldgen/chunk/chunk.cpp
        source/game/worldgen/chunkmanager/chunkmanager.cpp
        source/game/worldgen/mesh/mesh.cpp)

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
