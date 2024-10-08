#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec4 Color; // Varying
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float uTime;

void main()
{
    TexCoord = aTexCoord; // Pass-through
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}