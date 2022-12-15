#include "../shader/shader.h"
#include "../vertexarray/vertexarray.h"
#include "../vertexbuffer/vertexbuffer.h"
#include "../elementbuffer/elementbuffer.h"
#include "../gui/gui.h"
#include "../../game/worldgen/chunkmanager/chunkmanager.h"
#include "../window/window.h"

class Application {
public:
    void run();

private:
    Window *m_window;
    Camera *m_camera;
    Gui *m_gui;
    ChunkManager *m_chunkManager;
    Shader *m_blockShader;
};