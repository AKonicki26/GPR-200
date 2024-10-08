#version 330 core
out vec4 FragColor;

in vec4 Color; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float uTime;

void main()
{
    //FragColor = Color * ((sin(2 * uTime) / 2) + 0.5) ;
    vec4 texColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.4);
    if (texColor.a < 0.1)
        discard;
    FragColor = texColor;

    FragColor = vec4(TexCoord.x, TexCoord.y, 0.5f, 1.0f);
}