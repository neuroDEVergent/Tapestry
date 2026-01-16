 #version 410 core

 in vec3 v_vertexColors;
 in vec2 v_TexCoords;
 in vec4 v_vertexPosition;
  
 out vec4 FragColor;

 vec2 TexCent = vec2(0.5, 0.5);

 uniform vec2 mousePos;
 uniform float time;
 uniform sampler2D ourTexture;
 uniform float imageWidth;
 uniform float imageHeight;

 void main()
{
  vec2 uv = v_TexCoords;

  vec2 texel = vec2(1.0 / imageWidth, 1.0 / imageHeight);

  vec4 centerColor = texture(ourTexture, uv);
  float centerA = centerColor.a;

  float leftA  = texture(ourTexture, uv + vec2(-10.0,  0.0) * texel).a;
  float rightA = texture(ourTexture, uv + vec2( 10.0,  0.0) * texel).a;
  float upA    = texture(ourTexture, uv + vec2( 0.0,  10.0) * texel).a;
  float downA  = texture(ourTexture, uv + vec2( 0.0, -10.0) * texel).a;

  float maxNeighborDiff = max(
    max(abs(leftA - centerA), abs(rightA - centerA)),
    max(abs(upA   - centerA), abs(downA - centerA))
  );

  const float THRESHOLD = 0.05;

  bool isEdge = maxNeighborDiff > THRESHOLD;

  float dist = distance(mousePos, uv);
  float intensity = (-dist + 1.0) * 0.7;

  vec4 glowColor = vec4(0.6, 0.2, 0.7, centerA);
  vec4 backGlow = vec4(1, 0, 1, 1);

  float distCent = abs(distance(uv, TexCent)) * 2;
  distCent = (-distCent + 1.0);
  float distCentInten = (-distCent + 1.0) * 0.7;

  if (isEdge && centerA > 0.01)
  {
    FragColor = centerColor * 4.0;
  }

  /*
  else if (!isEdge && centerA <= 0.5)
  {
    FragColor.rgb = backGlow.rgb * intensity * 2.0;
    FragColor.a = maxNeighborDiff * 20.0;
  }
  */

  else
  {
    FragColor = centerColor;
    FragColor.rgb *= intensity * 2.0;
  }
}
