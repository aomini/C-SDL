#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>

#include <cstddef>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 540;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

bool init() {
  bool success = true;

  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize " << SDL_GetError() << endl;
    success = false;
  } else {
    // create window
    gWindow = SDL_CreateWindow("SDL Image formats", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      cout << "Window couldnot be created " << SDL_GetError() << endl;
      success = false;
    } else {
      // init PNG loading
      if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "SDL image could not be initialize! SDL_image error "
             << SDL_GetError() << endl;
        success = false;
      } else {
        // Get window surface
        gScreenSurface = SDL_GetWindowSurface(gWindow);
      }
    }
  }
  return success;
}

SDL_Surface* loadSurface(string path) {
  SDL_Surface* optimizedSurface = NULL;

  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    cout << "Unable to load image! SDL_image Error " << SDL_GetError() << endl;
  } else {
    optimizedSurface =
        SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      cout << "Unable to optimize image! SDL_image Error " << SDL_GetError()
           << endl;
    }
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

void close() {
  SDL_FreeSurface(gScreenSurface);
  gScreenSurface = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

void keepWindowOpen() {
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }
}

int main() {
  if (!init()) {
    cout << "SDL could not be initialized" << endl;
  } else {
    SDL_BlitSurface(loadSurface("assets/signature.png"), NULL, gScreenSurface,
                    NULL);
    // loadSurface("assets/signature.png");
    SDL_UpdateWindowSurface(gWindow);
    keepWindowOpen();
  }
  close();
  return EXIT_SUCCESS;
}
