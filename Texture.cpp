#include "Texture.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <iostream>


Texture::Texture(const char* filePath, unsigned int unit, TextureType type)
{
    glGenTextures(1, &ID);

    Unit = unit;
    Type = type;

    // load and generate the texture 
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format= GL_RGB;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filePath << std::endl;
        stbi_image_free(data);
    }
}

void Texture::Bind() const
{
    glActiveTexture(Unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

const char* Texture::GetTextureType() const
{
    switch (Type)
    {
    case Diffuse:return "diffuse";
    case Specular: return "specular";
    }
}
