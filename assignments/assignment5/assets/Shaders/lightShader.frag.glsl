#version 330 core
out vec4 FragColor;

in vec4 Color; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoord;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;


uniform float uTime;

void main()
{
    vec3 ambient = ambientStrength * lightColor;
}