cmake_minimum_required(VERSION 3.23)
project(voxerra)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
        src/core/glad/glad.c
        src/world-generation/FastNoiseLite.h
        src/world-generation/block.cpp
        src/world-generation/block.h
        src/world-generation/Chunk.cpp
        src/world-generation/Chunk.h
        src/world-generation/ChunkManager.cpp
        src/world-generation/ChunkManager.h
        src/world-generation/heightGenerator.cpp
        src/world-generation/heightGenerator.h
        src/main.cpp
        src/VBO.cpp
        src/EBO.cpp
        src/Shader.cpp
        src/VAO.cpp
        src/utils/enums.h
        src/utils/vert.cpp
        src/items/WeaponClass.cpp
        src/items/WeaponClass.h
        src/items/ArmorClass.cpp
        src/items/ArmorClass.h
        src/utils/Random.cpp
        src/utils/Random.h
        )

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
