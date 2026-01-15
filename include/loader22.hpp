#ifndef LOADER_HPP
#define LOADER_HPP

#include "sprite22.h"
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <vector>

void loadImage(Sprite& sprite, const std::string& texturePath);

void loadVertices(GLuint& VAO, GLuint& VBO, GLuint& EBO);

#endif
