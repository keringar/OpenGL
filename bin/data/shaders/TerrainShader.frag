#version 330 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D terrainTexture;

void main(){
    //color = texture(terrainTexture, TexCoord);
    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}