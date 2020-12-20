#version 460

uniform sampler2D texture1;

in vec2 voutTexCoord;

out vec4 FragColor;

void main()
{
    
    vec4 texColor = texture(texture1, voutTexCoord);

    if(texColor.a < 0.1){
        
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    
    else {
        FragColor = texColor; 
    }
    
}