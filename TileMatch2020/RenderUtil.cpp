#include "RenderUtil.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


GLuint LoadUtil::LoadTexture(std::string filepath)
{
    
    stbi_set_flip_vertically_on_load(true);

    GLuint textureGLID;
    glGenTextures(1, &textureGLID);

    glBindTexture(GL_TEXTURE_2D, textureGLID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int width;
    int height;
    int numChannels; 

    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &numChannels, 0);
        

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return textureGLID;

}

TextureHelp::TexCoordinates TextureHelp::GetAtlasCoordinates(int slotCountX, int slotCountY, int slot, int texSizeX, int texSizeY)
{
    {

        float halfPixelX = 1.0f / (2 * texSizeX);
        float halfPixelY = 1.0f / (2 * texSizeY);

        int gridX = slot % slotCountX;
        int gridY = slot / slotCountY;

        return TexCoordinates{ (1.0f / slotCountX) * gridX + halfPixelX,
                                (1.0f / slotCountX) * (gridX + 1) - halfPixelX,
                                (1.0f / slotCountY) * gridY + halfPixelY,
                                (1.0f / slotCountY) * (gridY + 1) - halfPixelY };

    }
}
