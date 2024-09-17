#version 330 core
out vec4 FragColor;
in vec4 Color; // the input variable from the vertex shader (same name and same type)

uniform float uTime;

void main()
{
    FragColor = Color * ((sin(2 * uTime) / 2) + 0.5) ;
}