#include "loader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void loadImage(Sprite& sprite, const std::string& texturePath)
{
  // Set parameters
  stbi_set_flip_vertically_on_load(true);
  glGenTextures(1, &sprite.textureID);
  glBindTexture(GL_TEXTURE_2D, sprite.textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // sbti image load
  unsigned char *image = stbi_load(texturePath.c_str(), &sprite.width, &sprite.height, &sprite.channels, 0);
  if (image)
  {
   // Depending on number of channels, we decide on the format
   GLenum format;
   if (sprite.channels == 1) format = GL_RED;
   else if (sprite.channels == 3) format = GL_RGB;
   else if (sprite.channels == 4) format = GL_RGBA;

   glTexImage2D(GL_TEXTURE_2D, 0, format, sprite.width, sprite.height, 0, format, GL_UNSIGNED_BYTE, image);
   glGenerateMipmap(GL_TEXTURE_2D);

   std::cout << "IMAGE LOADED" << std::endl;
   }

   else
   {
     std::cout << "ERROR LOADING THE IMAGE" << std::endl;
   }
   stbi_image_free(image);
}

void loadVertices(GLuint& VAO, GLuint& VBO, GLuint& EBO)
{
  const std::vector<GLfloat> vertexPosition{
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top left
     0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
     0.5f, -0.5f, 0.0f, 0.5f, 1.0f, 0.8f, 1.0f, 0.0f  // bottom right
  };

  const std::vector<GLint> indices{
     0, 1, 2, 2, 3, 1
  };

  // VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Start generating VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER,
               vertexPosition.size() * sizeof(GLfloat),
               vertexPosition.data(),
               GL_STATIC_DRAW
  );

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        8 * sizeof(GL_FLOAT),
                        (void*)0
                  );

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        8 * sizeof(GL_FLOAT),
                       (void*)(3 * sizeof(GL_FLOAT))
                 );

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        8 * sizeof(GL_FLOAT),
                        (void*)(6 * sizeof(GL_FLOAT))
  );

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLint), indices.data(), GL_STATIC_DRAW);

  glBindVertexArray(0);
  glDisableVertexAttribArray(0);
}
