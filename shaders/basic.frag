#version 330 core

out vec4 color;

uniform float time;

void main(){
    color = vec4(1.0f, 1.0f, 0.0f, 1.0f) * time;
}