#version 460

in vec2 vinPosition_2D; 
in vec2 vinTexCoord;

out vec2 voutTexCoord; 

void main(){

    voutTexCoord = vinTexCoord;
    gl_Position = vec4(vinPosition_2D, 0.0, 1.0);

}