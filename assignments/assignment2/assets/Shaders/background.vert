#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 Color; // Varying
out vec2 TexCoord;

uniform float uTime;

void main()
{
    Color = aColor; // Pass-through
    TexCoord = aTexCoord; // Pass-through
    vec3 pos = aPos;
    pos.y += sin((2 * uTime) - pos.x) / 12.0;
    pos *= 3; // Scale shader to take up entire background
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);

}