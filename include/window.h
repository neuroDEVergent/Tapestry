#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

// Main window struct
typedef struct
{
  SDL_Window*   graphicsApplicationWindow;
  SDL_GLContext openGLContext;

  int           width;
  int           height;
  const char*   title;

  bool          vsync;
  bool          quit;

  float         mouseAbsX;
  float         mouseAbsY;
  float         mouseNormX;
  float         mouseNormY;
} Window;

// Creates window + OpenGL context
// returns true on success, false on failure
bool createWindow(
  Window*       window,
  int           width,
  int           height,
  const char*   title,
  bool          vsync = true
);


// Destroys everything
void destroyWindow(Window* window);

// Called once per frame to process SDL events
// Returns false if quit is called
void pollEvents(Window* window);


#endif
