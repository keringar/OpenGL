#version 330 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D terrainTexture;

void main(){
    color = texture(terrainTexture, TexCoord);
}