 #version 410 core

 in vec3 v_vertexColors;
 in vec2 v_TexCoords;

 out vec4 color;

 uniform int enable;
 uniform vec3 dynamicColor;
 uniform sampler2D ourTexture;

 void main()
{
  color = texture(ourTexture, v_TexCoords);
}
