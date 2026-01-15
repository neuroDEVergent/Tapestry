#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// Personal libraries
#include "spriterenderer22.hpp"
#include "shader.h"
#include "loader22.hpp"
#include "sprite.h"
#include "window.h"

// Globals
GLuint VAO = 0;
GLuint VBO = 0;
GLuint EBO = 0;

float leftRight = 0;
float upDown = 0;

float deltaTime = 0;
float lastFrame = 0;

int main()
{
    Window win = {0};
    if (!createWindow(&win, 1280, 720, "SDL Window", true))
    {
      return 1;
    }

    GLuint ourShader = createGraphicsPipeline("./shaders/vert.glsl","./shaders/frag.glsl");
    
    Sprite minecraft = {0};
    minecraft.posX = 2;
    minecraft.posY = 2;
    loadImageAsTexture(&minecraft, "./minecraft.png");

    Sprite girlyPop = {0};
    loadImageAsTexture(&girlyPop, "./girlypop.png");

    leftRight = 630;
    upDown = 361;

    loadVertices(VAO, VBO, EBO);

    //Sprite ourSprite2("./minecraft.png");
    //Sprite girlyPop("./girlypop.png");

    while (!win.quit)
    {
      pollEvents(&win);
      float currentFrame = static_cast<float>(SDL_GetTicks()); 
      deltaTime = (currentFrame - lastFrame) / 1000.0f;
      lastFrame = currentFrame;

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);
      glViewport(0, 0, win.width, win.height);
      glClearColor(.03f, .05f, 0.27f, 1.f);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      // Magic happens here
//      renderer.draw(wall);
      girlyPop.posX = leftRight;
      girlyPop.posY = upDown;
//      renderer.draw(girlyPop);
      draw(minecraft, VAO, &ourShader);
      draw(girlyPop, VAO, &ourShader);
    
      //

      SDL_GL_SwapWindow(win.graphicsApplicationWindow);
    }

    destroyWindow(&win);
    return 0;

}
