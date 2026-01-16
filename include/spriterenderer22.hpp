#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "sprite.h"
#include "window.h"

void draw(Sprite& sprite, GLuint& VAO, GLuint* shader, Window* window, float time);

#endif
