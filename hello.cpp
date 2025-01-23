#include <SDL2/SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstdlib>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
  cout << "Starting.." << endl;
  // The rendering window
  SDL_Window *window = NULL;

  // The surfaced contained by the window
  SDL_Surface *screenSurface = NULL;

  // Init SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {

    cout << "SDL count not be initialized" << SDL_GetError() << endl;
    return EXIT_FAILURE;
  }
  // Create window

  window =
      SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    cout << "Window could not be create: SDL ERROR " << SDL_GetError() << endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  // Get window surface
  screenSurface = SDL_GetWindowSurface(window);
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);

  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
