#include "vector"
#include "iostream"

#include "core/VertexArray.h"
#include "core/VertexBuffer.h"
#include "core/ElementBuffer.h"
#include "core/Shader.h"
#include "core/debuggui/DebugGui.h"
#include "game/Camera/Camera.h"
#include "game/worldgen/chunkmanager/ChunkManager.h"

#include "core/application/Application.h"

int main() {
    Application application(true);
    application.Run();
    return EXIT_SUCCESS;


    // initialize glfw


    // initialize glad


    // opengl error callback

    // generate chunks
/*    std::vector<Chunk *> chunks;
    ChunkManager chunkManager;
    chunkManager.GenerateChunks(8, 8);
    std::cout << "generated chunks" << std::endl;
    chunkManager.GetChunks(chunks);
    std::vector<float> worldVertices;
    std::vector<unsigned int> worldIndices;

    for (Chunk *chunk: chunks) {
        std::vector<float> chunkVertices;
        std::vector<unsigned int> chunkIndices;
        chunk->GetVertices(chunkVertices);
        chunk->GetIndices(chunkIndices);

        worldVertices.insert(worldVertices.end(), chunkVertices.begin(), chunkVertices.end());
        worldIndices.insert(worldIndices.end(), chunkIndices.begin(), chunkIndices.end());
    }

    std::cout << "vertices length: " << worldVertices.size() << std::endl;
    std::cout << "indices length: " << worldIndices.size() << std::endl;

    // create vertex array object
    VertexArray vao;
    vao.Bind();

    // create vertex buffer object
    VertexBuffer vbo;
    vbo.Bind();
    vbo.SetData(worldVertices.data(), worldVertices.size() * sizeof(float));

    // create element buffer object
    ElementBuffer ebo;
    ebo.Bind();
    ebo.SetData(worldIndices.data(), worldIndices.size() * sizeof(unsigned int));
*/
    // set vertex attributes


    // unbind vertex array object
    //vao.Unbind();

    // cube shader
    Shader blockShader("shaders/block.vert", "shaders/block.frag");

    blockShader.SetMat4("viewMatrix", camera->viewMatrix);
}