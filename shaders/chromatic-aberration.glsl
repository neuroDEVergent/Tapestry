 #version 410 core

 in vec3 v_vertexColors;
 in vec2 v_TexCoords;
 in vec4 v_vertexPosition;

 vec2 center = vec2(0.5, 0.5);
  
 out vec4 FragColor;

 uniform vec2 mousePos;
 uniform float time;
 uniform sampler2D ourTexture;
 uniform float imageWidth;
 uniform float imageHeight;

 void main()
{
  float dist = distance(mousePos, center);
  dist = dist * 2;
  float intensity = dist * 20;
  
  float w = 1 / imageWidth;
  float h = 1 / imageHeight;

  FragColor.r = texture(ourTexture, v_TexCoords - vec2(w*intensity, 0.0)).r;
  FragColor.g = texture(ourTexture, v_TexCoords).g;
  FragColor.b = texture(ourTexture, v_TexCoords - vec2(0.0, h*intensity)).b;
  FragColor.a = 1.0;

}
