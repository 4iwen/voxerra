#include "glad/glad.h"

class FrameBuffer {
public:
    unsigned int ID;

    FrameBuffer();
    ~FrameBuffer();
    void Bind();
    void Unbind();
};