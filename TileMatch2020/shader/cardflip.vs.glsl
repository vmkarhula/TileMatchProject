#version 460

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vinColor;

out vec3 voutColor;

uniform mat4 modelMtx;
uniform mat4 viewMtx;
uniform mat4 projMtx;

void main(){

    voutColor = vinColor;
    gl_Position =  projMtx * viewMtx * modelMtx * vec4(vPosition, 1.0);


}