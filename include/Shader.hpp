#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
  public:
    GLuint ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
      ID = glCreateProgram();

      std::string vString = LoadShaderAsString(vertexPath);
      std::string fString = LoadShaderAsString(fragmentPath);

      GLuint myVertex = CompileShader(GL_VERTEX_SHADER, vString);
      GLuint myFragment = CompileShader(GL_FRAGMENT_SHADER, fString);

      glAttachShader(ID, myVertex);
      glAttachShader(ID, myFragment);
      glLinkProgram(ID);

      glValidateProgram(ID);

      glDetachShader(ID, myVertex);
      glDetachShader(ID, myFragment);

      glDeleteShader(myVertex);
      glDeleteShader(myFragment);
    }

    void use()
    {
      glUseProgram(ID);
    }

    void deleteShader()
    {
      glDeleteProgram(ID);
    }

    void uniformMatrix4(const std::string& name, glm::mat4 mat)
    {
      GLuint location = glGetUniformLocation(ID, name.c_str());
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }

    void uniform1f(const std::string& name, float value)
    {
      GLuint location = glGetUniformLocation(ID, name.c_str());
      glUniform1f(location, value);
    }

    void uniform2f(const std::string& name, float value1, float value2)
    {
      GLuint location = glGetUniformLocation(ID, name.c_str());
      glUniform2f(location, value1, value2);
    }

    void uniform3f(const std::string& name, float value1, float value2, float value3)
    {
      GLuint location = glGetUniformLocation(ID, name.c_str());
      glUniform3f(location, value1, value2, value3);
    }

    void uniform4f(const std::string& name, float value1, float value2, float value3, float value4)
    {
      GLuint location = glGetUniformLocation(ID, name.c_str());
      glUniform4f(location, value1, value2, value3, value4);
    }

  private:

    std::string LoadShaderAsString(const std::string& filename)
    {
      std::string result = "";

      std::string line = "";
      std::ifstream myFile(filename.c_str());

      if (myFile.is_open())
      {
        while (std::getline(myFile, line))
        {
          result += line + '\n';
        }
        myFile.close();
      }

      return result;
    }
    
    GLuint CompileShader(GLuint type, const std::string& source)
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

      const char* src = source.c_str();
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

        if (type == GL_VERTEX_SHADER) std::cout << "ERROR: VERTEX SHADER COMPILATION FAILED\n" << errorMessages << std::endl;
        if (type == GL_FRAGMENT_SHADER) std::cout << "ERROR: FRAGMENT SHADER COMPILATION FAILED\n " << errorMessages << std::endl;
		
		delete[] errorMessages;
		glDeleteShader(shaderObject);
      }

      return shaderObject;
    }
};

#endif
