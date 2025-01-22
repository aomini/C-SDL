#include <SDL2/SDL.h>
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
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    cout << "SDL count not be initialized" << SDL_GetError() << endl;
  else
    cout << "SDL Initialized" << endl;

  return EXIT_SUCCESS;
}
