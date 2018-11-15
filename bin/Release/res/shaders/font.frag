#version 330 core

layout (location = 0) out vec4 fColor;

in vec2 texCoord;

uniform sampler2D uTexture;
uniform vec4 uTextColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTexture, texCoord).r);
    fColor = uTextColor * sampled;
}  