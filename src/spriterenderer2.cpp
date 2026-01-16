#include "spriterenderer22.hpp"

int screenWidth = 1280;
int screenHeight = 720;

void draw(Sprite& sprite, GLuint& VAO, GLuint* shader, Window* window, float time)
{
  glUseProgram(*shader);
  glBindVertexArray(VAO);
  // Texture binding
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, sprite.textureID);

  // Model matrix
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(sprite.posX, sprite.posY, 0.0f));
  model = glm::scale(model, glm::vec3(sprite.width *0.35f, sprite.height *0.35f, 1.0f));
  // model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

  uniformMatrix4(shader, "model", model);

  // Orthogonal projection matrix
  glm::mat4 projection = glm::mat4(1.0f);
  float aspect = (float)window->width / (float)window->height;
  projection = glm::ortho(0.0f, (float)window->width, 0.0f, (float)window->height, -0.1f, 0.1f);
  uniformMatrix4(shader, "projection", projection);

  uniform2f(shader, "mousePos", window->mouseNormX, window->mouseNormY);
  uniform1f(shader, "time", time);
//  printf("time: %f\n", time);

  // Draw call
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

