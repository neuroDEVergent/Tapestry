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

  /*

  // Black and white filter
  for (int i = 0; i < 10; i++)
  {
    float avg = (n[i].r + n[i].g + n[i].b) / 3;
    n[i] = vec4(vec3(avg), 1.0);
  }

  // Sobel kernel calculation
  vec4 sobel_edge_h = n[0] + (2.0*n[1]) + n[2] - (n[6] + (2.0*n[7]) + n[8]);
  vec4 sobel_edge_v = n[2] + (2.0*n[5]) + n[8] - (n[0] + (2.0*n[3]) + n[6]);
  vec4 sobel = sqrt((sobel_edge_h * sobel_edge_h) + (sobel_edge_v * sobel_edge_v));
  */

  float I[9];
  for (int i = 0; i < 10; i++)
  {
    I[i] = dot(n[i].rgb, vec3(0.299, 0.587, 0.114));
  }

  float laplacian = (
    (I[0] * -1.0) + (I[1] * -1.0) + (I[2] * -1.0) +
    (I[3] * -1.0) + (I[4] * 8) +    (I[5] * -1.0) +
    (I[6] * -1.0) + (I[7] * -1.0) + (I[8] * -1.0)
  );

  float edge = abs(laplacian);


  FragColor = vec4(vec3(edge), 1.0);
}
