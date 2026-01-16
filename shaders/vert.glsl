#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 vertexColors;
layout(location=2) in vec2 TexCoords;

uniform mat4 projection;
uniform mat4 model;

out vec3 v_vertexColors;
out vec2 v_TexCoords;
out vec4 v_vertexPosition;

void main()
{
  v_vertexColors = vertexColors;
  v_vertexPosition = projection * model * vec4(position, 1.0f);
  v_TexCoords = TexCoords;
  gl_Position = v_vertexPosition;

}
