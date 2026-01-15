#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>

typedef struct 
{
  GLuint textureID;
  int width;
  int height;
  int channels;

  float posX;
  float posY;
} Sprite;

void loadImageAsTexture(Sprite* sprite, const char* filePath);

#endif
