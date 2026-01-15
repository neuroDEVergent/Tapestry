#include "loader22.hpp"

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
