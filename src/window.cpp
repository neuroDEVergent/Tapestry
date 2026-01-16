#include "window.h"
#include <stdio.h>
#include <iostream>
#include <glad/glad.h>

bool createWindow(
  Window*       window,
  int           width,
  int           height,
  const char*   title,
  bool          vsync
)
{
  if (!window) return false;

  *window = {0};

  window->width   = width;
  window->height  = height;
  window->title   = title;
  window->vsync   = vsync;
  window->quit    = false;
  
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

  window->graphicsApplicationWindow = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  if (window->graphicsApplicationWindow == nullptr)
  {
      std::cout << "SDL Window was not able to be created" << std::endl;
      exit(1);
  }

  window->openGLContext = SDL_GL_CreateContext(window->graphicsApplicationWindow);

  if (window->openGLContext == nullptr)
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

  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  return true;
}

void destroyWindow(Window* window)
{
  if (!window) return;

  if (window->openGLContext)
  {
    SDL_GL_DeleteContext(window->openGLContext);
    window->openGLContext = NULL;
  }

  if (window->graphicsApplicationWindow)
  {
    SDL_DestroyWindow(window->graphicsApplicationWindow);
    window->graphicsApplicationWindow = NULL;
  }

  *window = {0};

}

void pollEvents(Window* window)
{
  SDL_Event e;
    
  while (SDL_PollEvent(&e) != 0)
  {
    switch (e.type)
    {
      case SDL_QUIT:
        std::cout << "Goodbye!" << std::endl;
        window->quit = true;

      case SDL_WINDOWEVENT:
        if (e.window.event == SDL_WINDOWEVENT_CLOSE)
        {
          window->quit = true;
        }

      case SDL_MOUSEMOTION:
        window->mouseAbsX = (float) e.motion.x;
        window->mouseAbsY = (float) -e.motion.y + window->height;

        window->mouseNormX = (float) e.motion.x / window->width;
        window->mouseNormY = (float) -e.motion.y / window->height + 1;
       // TODO handle window resize event
    }


  
  }
}
