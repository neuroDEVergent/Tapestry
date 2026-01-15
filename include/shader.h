#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdlib.h>

GLuint createGraphicsPipeline(const char* vertexPath, const char* fragmentPath);
void uniformMatrix4(GLuint* ID, const char* name, glm::mat4 mat);
void uniform1f(GLuint* ID, const char* name, float val1);
void uniform2f(GLuint* ID, const char* name, float val1, float val2);
void uniform3f(GLuint* ID, const char* name, float val1, float val2, float val3);
void uniform4f(GLuint* ID, const char* name, float val1, float val2, float val3, float val4);
char *LoadShaderAsString(const char* filename);
GLuint CompileShader(GLuint type, const char* source);

#endif
