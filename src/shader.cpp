#include "shader.h"

GLuint createGraphicsPipeline(const char* vertexPath, const char* fragmentPath)
{
  GLuint ID = glCreateProgram();
  
  GLuint myVertex = CompileShader(GL_VERTEX_SHADER, LoadShaderAsString(vertexPath));

  GLuint myFragment = CompileShader(GL_FRAGMENT_SHADER, LoadShaderAsString(fragmentPath));

  glAttachShader(ID, myVertex);
  glAttachShader(ID, myFragment);
  glLinkProgram(ID);

  glValidateProgram(ID);

  glDetachShader(ID, myVertex);
  glDetachShader(ID, myFragment);

  glDeleteShader(myVertex);
  glDeleteShader(myFragment);

  return ID;
}

void uniformMatrix4(GLuint* ID, const char* name, glm::mat4 mat)
{
  glUniformMatrix4fv(glGetUniformLocation(*ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void uniform1f(GLuint* ID, const char* name, float val)
{
  glUniform1f(glGetUniformLocation(*ID, name), val);
}

void uniform2f(GLuint* ID, const char* name, float val1, float val2)
{
  glUniform2f(glGetUniformLocation(*ID, name), val1, val2);
}

void uniform3f(GLuint* ID, const char* name, float val1, float val2, float val3)
{
  glUniform3f(glGetUniformLocation(*ID, name), val1, val2, val3);
}

void uniform4f(GLuint* ID, const char* name, float val1, float val2, float val3, float val4)
{
  glUniform4f(glGetUniformLocation(*ID, name), val1, val2, val3, val4);
}

char *LoadShaderAsString(const char* filename)
{
  FILE *file = fopen(filename, "r");
  if (!file) return NULL;

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = (char*)malloc(size + 1);
  if (!buffer)
  {
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, size, file);
  buffer[size] = '\0';

  fclose(file);
  return buffer;
}

GLuint CompileShader(GLuint type, const char* source)
{
  GLuint shaderObject = 0;
  
  if (type == GL_VERTEX_SHADER)
  {
    shaderObject = glCreateShader(GL_VERTEX_SHADER);
  }

  else if (type == GL_FRAGMENT_SHADER)
  {
     shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
  }

   const char* src = source;
   glShaderSource(shaderObject, 1, &src, nullptr);
   glCompileShader(shaderObject);

   int result;

   glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

   if (result == GL_FALSE)
   {
     int length;
     glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
     char *errorMessages = new char[length];
     glGetShaderInfoLog(shaderObject, length, &length, errorMessages);

     if (type == GL_VERTEX_SHADER) printf("ERROR: VERTEX SHADER COMPILATION FAILED\n%s\n", errorMessages);
     if (type == GL_FRAGMENT_SHADER) printf("ERROR: FRAGMENT SHADER COMPILATION FAILED\n%s\n", errorMessages);
		
	   delete[] errorMessages;
		 glDeleteShader(shaderObject);
    }

   return shaderObject;
}
