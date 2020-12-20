#version 460

uniform sampler2D texture1;
uniform vec4 atlasCoordinates; 

in vec2 voutTexCoord;

out vec4 FragColor;

void main()
{

    vec2 AtlasTranslated = vec2(atlasCoordinates[0] + voutTexCoord.x * (atlasCoordinates[1] - atlasCoordinates[0]),
                                atlasCoordinates[2] + voutTexCoord.y * (atlasCoordinates[3]- atlasCoordinates[2]));

    vec4 texColor = texture(texture1, AtlasTranslated);

    if(texColor.a < 0.1){
        
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    
    else {
        FragColor = texColor; 
    }
}