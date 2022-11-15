#include "../window/Window.h"
#include "../Shader.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../ElementBuffer.h"
#include "../debuggui/DebugGui.h"
#include "../../game/worldgen/chunkmanager/ChunkManager.h"

class Application {
public:
    Application(bool debug = false);

    ~Application();

    void Run();

    Window *window;
    Camera *camera;
    DebugGui *debugGui;
    ChunkManager *chunkManager;
};