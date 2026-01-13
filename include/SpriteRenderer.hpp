#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shader.hpp>


class SpriteRenderer
{
  public:
  Shader& shader;

    // Constructor, we take the shader and screen width and height
    SpriteRenderer(Shader& shader, int scrW, int scrH) : shader(shader)
    {
      screenWidth = scrW;
      screenHeight = scrH;
      vertexSpecification();
    }

    // Called every frame
    // TODO reduce the complexity of the function call by passing only floats
    void draw(Sprite& sprite)
    {
      shader.use();

      glBindVertexArray(VAO);

      // Texture binding
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, sprite.textureID);

      // Model matrix
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(sprite.posX, sprite.posY, 0.0f));
      model = glm::scale(model, glm::vec3(sprite.width, sprite.height, 1.0f));
//      model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
      shader.uniformMatrix4("model", model);

      // Orthogonal projection matrix
      glm::mat4 projection = glm::mat4(1.0f);
      float aspect = (float)screenWidth / (float)screenHeight;
      projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -0.1f, 0.1f);
      shader.uniformMatrix4("projection", projection);

      // Draw call
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   
    }

  private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
    int screenWidth = 0;
    int screenHeight = 0;

    // x, y, z, r, g, b, TextureX, TextureY
    void vertexSpecification()
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

};

#endif
