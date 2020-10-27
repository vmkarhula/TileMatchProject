#version 460

layout (location=0) in vec3 vPosition;
layout (location=1) in vec3 vinColor;

out vec3 voutColor;

void main(){

    voutColor = vinColor;
    gl_Position = vec4(vPosition, 1.0);
    
}
