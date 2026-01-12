#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Sprite
{
  public:
    // All we keep for now is sprite's texture ID
    // TODO implement position, scale, rotation and color data
    GLuint texture;

    // Constructor
    Sprite(const std::string& texturePath)
    {
      loadImage(texturePath);
    }

  private:
    // Loading the image using sbti library
    void loadImage(const std::string& texturePath)
    {
      stbi_set_flip_vertically_on_load(true);
      // Setting up texture and it's parameters
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      // sbti image load
      int width, height, channels;
      unsigned char *image = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
      if (image)
      {
        // Depending on number of channels, we decide on the format
        GLenum format;
        if (channels == 1) format = GL_RED;
        else if (channels == 3) format = GL_RGB;
        else if (channels == 4) format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
      glGenerateMipmap(GL_TEXTURE_2D);

      std::cout << "IMAGE LOADED" << std::endl;
      }

      else
      {
        std::cout << "ERROR LOADING THE IMAGE" << std::endl;
      }
      stbi_image_free(image);
    }

};



#endif
