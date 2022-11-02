#version 330 core

layout (location = 0) in vec3 pos;

uniform vec3 lightColor;

out vec3 color;

void main()
{
    gl_Position = vec4(pos, 1.0);
    color = lightColor;
}