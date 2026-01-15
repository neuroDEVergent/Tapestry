#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>

struct Sprite
{
  GLuint textureID;
  int width;
  int height;
  int channels;

  float posX;
  float posY;
};

#endif
