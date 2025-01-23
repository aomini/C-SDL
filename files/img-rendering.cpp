#include <SDL2/SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 540;

bool init();
bool loadmedia();
void close();
void keepWindowOpen();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* imageSurface = NULL;

int main(int argc, char* args[]) {
  if (!init()) {
    cout << "Failed to init" << endl;
  } else {
    if (!loadmedia()) {
      cout << "failed to load media " << endl;
    } else {
      // Apply the image
      SDL_BlitSurface(imageSurface, NULL, gScreenSurface, NULL);
      SDL_UpdateWindowSurface(gWindow);
      keepWindowOpen();
    }
  }
  close();
  return EXIT_SUCCESS;
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

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL count not initialize! " << SDL_GetError() << endl;
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("Image on screen", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      cout << "Window could not be created! " << SDL_GetError();
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadmedia() {
  bool success = true;
  imageSurface = SDL_LoadBMP("assets/hello_world.bmp");
  if (imageSurface == NULL) {
    cout << "Unable to load image " << SDL_GetError() << endl;
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(imageSurface);
  imageSurface = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}
