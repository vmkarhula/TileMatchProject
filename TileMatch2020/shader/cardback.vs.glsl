#version 460

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vinTexCoord;

out vec2 voutTexCoord;

uniform mat4 modelMtx;
uniform mat4 viewMtx;
uniform mat4 projMtx;

void main(){

    voutTexCoord = vinTexCoord;
    gl_Position =  projMtx * viewMtx * modelMtx * vec4(vPosition, 1.0);


}