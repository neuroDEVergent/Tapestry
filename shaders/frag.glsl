 #version 410 core

 in vec3 v_vertexColors;
 in vec2 v_TexCoords;
 in vec4 v_vertexPosition;
  
 vec2 center = vec2(0.5, 0.5);

 out vec4 color;

 uniform vec2 mousePos;
 uniform float time;
 uniform sampler2D ourTexture;

 void main()
{
  vec2 uv = v_TexCoords;

  float dist = distance(center, v_TexCoords);
  float intensity = -distance(mousePos, center) + 1;

  float glow = 0.1 / dist;
  glow = clamp(glow, 0., 1.);

  vec3 glowColor = vec3(0.6, 0.2, 0.7);

  color = texture(ourTexture, v_TexCoords);
  color += vec4(glowColor, 0.0f) *intensity * glow * 1.5;

}
