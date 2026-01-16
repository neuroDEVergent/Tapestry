 #version 410 core

 in vec3 v_vertexColors;
 in vec2 v_TexCoords;
 in vec4 v_vertexPosition;
  
 out vec4 FragColor;

 uniform vec2 mousePos;
 uniform float time;
 uniform sampler2D ourTexture;
 uniform float imageWidth;
 uniform float imageHeight;

 void main()
{

  float w = 1.0 / imageWidth;
  float h = 1.0 / imageHeight;

  vec4 n[9];

  n[0] = texture(ourTexture, v_TexCoords + vec2(-w,  -h));
  n[1] = texture(ourTexture, v_TexCoords + vec2(0.0, -h));
  n[2] = texture(ourTexture, v_TexCoords + vec2( w,  -h));

  n[3] = texture(ourTexture, v_TexCoords + vec2(-w, 0.0));
  n[4] = texture(ourTexture, v_TexCoords);
  n[5] = texture(ourTexture, v_TexCoords + vec2( w, 0.0));

  n[6] = texture(ourTexture, v_TexCoords + vec2(-w,  h));
  n[7] = texture(ourTexture, v_TexCoords + vec2(0.0, h));
  n[8] = texture(ourTexture, v_TexCoords + vec2( w,  h));

  vec4 sobel_edge_h = n[0] + (2.0*n[1]) + n[2] - (n[6] + (2.0*n[7]) + n[8]);
  vec4 sobel_edge_v = n[2] + (2.0*n[5]) + n[8] - (n[0] + (2.0*n[3]) + n[6]);
  vec4 sobel = sqrt((sobel_edge_h * sobel_edge_h) + (sobel_edge_v * sobel_edge_v));

  FragColor = vec4(sobel.rgb, 1.0);
}
