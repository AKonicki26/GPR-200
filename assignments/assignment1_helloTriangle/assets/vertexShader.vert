#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 Color; // Varying

uniform float uTime;

void main()
{
    Color = aColor; // Pass-through
    vec3 pos = aPos;
    pos.y += sin((2 * uTime) - pos.x) / 4.0;
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}