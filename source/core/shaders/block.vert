#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 blockColor;

uniform mat4 viewMatrix;

out vec3 color;

void main()
{
    gl_Position = viewMatrix * vec4(pos, 1.0f);
    color = blockColor;
}