#version 330 core
out vec4 FragColor;

in vec4 Color; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoord;

uniform sampler2D _texture;

uniform float uTime;

void main()
{
    vec4 texColor = texture(_texture, TexCoord);
    if (texColor.a < 0.1)
            discard;
    FragColor = texColor;
}