#include "sprite.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void loadImageAsTexture(Sprite* sprite, const char* filePath)
{
  // Set parameters
  stbi_set_flip_vertically_on_load(true);
  glGenTextures(1, &sprite->textureID);
  glBindTexture(GL_TEXTURE_2D, sprite->textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // sbti image load
  unsigned char *image = stbi_load(filePath, &sprite->width, &sprite->height, &sprite->channels, 0);
  if (image)
  {
   // Depending on number of channels, we decide on the format
   GLenum format;
   if (sprite->channels == 1) format = GL_RED;
   else if (sprite->channels == 3) format = GL_RGB;
   else if (sprite->channels == 4) format = GL_RGBA;

   glTexImage2D(GL_TEXTURE_2D, 0, format, sprite->width, sprite->height, 0, format, GL_UNSIGNED_BYTE, image);
   glGenerateMipmap(GL_TEXTURE_2D);

   printf("IMAGE LOADED\n");
   }
   else
   {
    printf("ERROR LOADING THE IMAGE\n");
   }
   stbi_image_free(image);
}
