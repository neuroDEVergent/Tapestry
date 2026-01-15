#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "sprite.h"

void draw(Sprite& sprite, GLuint& VAO, GLuint* shader);

#endif
