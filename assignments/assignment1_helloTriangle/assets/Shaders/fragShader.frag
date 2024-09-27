#version 330 core
out vec4 FragColor;

in vec4 Color; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform float uTime;

void main()
{
    //FragColor = Color * ((sin(2 * uTime) / 2) + 0.5) ;
    vec4 texColor = texture(ourTexture, TexCoord);
    if (texColor.a < 0.1)
            discard;
    FragColor = texColor;
}