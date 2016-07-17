#version 330 core

in vec2 TexCoord;

out vec4 outColor;

uniform sampler2D inTexture;

void main(){
    outColor = texture(inTexture, TexCoord);
}