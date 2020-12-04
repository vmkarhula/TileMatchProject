#include "RenderUtil.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


GLuint LoadUtil::LoadTexture(std::string filepath)
{
    
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
        

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);


    return textureGLID;

}
