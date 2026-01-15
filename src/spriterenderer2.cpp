#include "spriterenderer22.hpp"

int screenWidth = 1280;
int screenHeight = 720;

void draw(Sprite& sprite, GLuint& VAO, Shader& shader)
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
  // model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
  shader.uniformMatrix4("model", model);

  // Orthogonal projection matrix
  glm::mat4 projection = glm::mat4(1.0f);
  float aspect = (float)screenWidth / (float)screenHeight;
  projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -0.1f, 0.1f);
  shader.uniformMatrix4("projection", projection);

  // Draw call
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

