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
#include "spriterenderer.hpp"
#include "sprite.h"
#include "loader.hpp"

// Globals
int gScreenWidth = 1280;
int gScreenHeight = 720;
SDL_Window* gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;
bool gQuit = false; // If true we quit
GLuint VAO = 0;
GLuint VBO = 0;
GLuint EBO = 0;

float leftRight = 0;
float upDown = 0;

float deltaTime = 0;
float lastFrame = 0;

void GetOpenGLVersionInfo()
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


void InitializeSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL2 could not initialize video subsystem" << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 2);

    gGraphicsApplicationWindow = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (gGraphicsApplicationWindow == nullptr)
    {
        std::cout << "SDL Window was not able to be created" << std::endl;
        exit(1);
    }

    gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);

    if (gOpenGLContext == nullptr)
    {
        std::cout << "OpenGL context could not be created" << std::endl;
        exit(1);
    }

    // Initialize the Glad Library
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "glad was not initialized" << std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();
}

void Input()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
          case SDL_QUIT:
            std::cout << "Goodbye!" << std::endl;
            gQuit = true;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A]) leftRight -= 1.0f;
    if (state[SDL_SCANCODE_D]) leftRight += 1.0f;
    if (state[SDL_SCANCODE_W]) upDown += 1.0f;
    if (state[SDL_SCANCODE_S]) upDown -= 1.0f;
}

int main()
{
    InitializeSDL();


    Shader ourShader("./shaders/vert.glsl","./shaders/frag.glsl");
    Sprite wall;
    wall.posX = 2;
    wall.posY = 2;
    loadImage(wall, "./wall.jpg");

    Sprite minecraft;
    minecraft.posX = 1;
    minecraft.posY = 1;
    loadImage(minecraft, "./minecraft.png");

    Sprite girlyPop;
    loadImage(girlyPop, "./girlypop.png");
    leftRight = 630;
    upDown = 361;

    loadVertices(VAO, VBO, EBO);

    //Sprite ourSprite2("./minecraft.png");
    //Sprite girlyPop("./girlypop.png");

    while (!gQuit)
    {
      float currentFrame = static_cast<float>(SDL_GetTicks()); 
      deltaTime = (currentFrame - lastFrame) / 1000.0f;
      lastFrame = currentFrame;

      Input();
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);
      glViewport(0, 0, gScreenWidth, gScreenHeight);
      glClearColor(.03f, .05f, 0.27f, 1.f);
      glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      // Magic happens here
//      renderer.draw(wall);
      minecraft.posX = leftRight;
      minecraft.posY = upDown;
      std::cout << "X: " << leftRight << std::endl;
      std::cout << "Y: " << upDown << std::endl;
//      renderer.draw(girlyPop);
      draw(minecraft, VAO, ourShader);
    
      //

      SDL_GL_SwapWindow(gGraphicsApplicationWindow);
    }

    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();

    return 0;

}
