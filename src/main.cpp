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
#include "spriterenderer.h"
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
    
    Sprite girlyPop = {0};
    loadImageAsTexture(&girlyPop, "./assets/girlypop.png");

    Sprite mount = {0};
//    loadImageAsTexture(&mount, "./assets/mount.png");

    Sprite obelisk = {0};
//    loadImageAsTexture(&obelisk, "./Sussy_Obelisk.png");

    Sprite pika = {0};
//    loadImageAsTexture(&pika, "./pika.png");

    leftRight = 630;
    upDown = 361;

    loadVertices(VAO, VBO, EBO);

    while (!win.quit)
    {
      pollEvents(&win);
      float currentFrame = static_cast<float>(SDL_GetTicks()) / 1000.0f; 
      deltaTime = (currentFrame - lastFrame);
      lastFrame = currentFrame;

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glViewport(0, 0, win.width, win.height);
      glClearColor(.00f, .00f, 0.00f, 1.f);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      // Magic happens here
      girlyPop.posX = leftRight;
      girlyPop.posY = upDown;
      draw(girlyPop, VAO, &ourShader, &win, currentFrame);
    
      //

      SDL_GL_SwapWindow(win.graphicsApplicationWindow);
    }

    destroyWindow(&win);
    return 0;

}
