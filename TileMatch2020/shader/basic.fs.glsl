#version 460

in vec3 voutColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(voutColor, 1.0f);
}