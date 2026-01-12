#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <string>
#include <fstream>
#include "SpriteRenderer.hpp"
#include "Sprite.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// Globals
int gScreenWidth = 640;
int gScreenHeight = 480;
SDL_Window* gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;
bool gQuit = false; // If true we quit

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
    //if (state[SDL_SCANCODE_A]) direction.x -= 1.0f;
    //if (state[SDL_SCANCODE_D]) direction.x += 1.0f;
}

int main()
{
    InitializeSDL();


    Shader ourShader("./shaders/vert.glsl","./shaders/frag.glsl");
    SpriteRenderer renderer(ourShader, gScreenWidth, gScreenHeight);

    Sprite ourSprite("./wall.jpg");
    Sprite ourSprite2("./minecraft.png");
    Sprite girlyPop("./girlypop.png");

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
      renderer.draw(ourSprite, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f, glm::vec3(1.0f));

      renderer.draw(ourSprite2, glm::vec2(1.0f, 1.0f), glm::vec2(0.5f, 0.5f), 0.0f, glm::vec3(1.0f));

      renderer.draw(girlyPop, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f, glm::vec3(1.0f));

    
      //

      SDL_GL_SwapWindow(gGraphicsApplicationWindow);
    }

    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();

    return 0;

}
