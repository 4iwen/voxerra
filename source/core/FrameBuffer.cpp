#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &ID);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &ID);
}

void FrameBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void FrameBuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}