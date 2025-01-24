#include <SDL2/SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include <iostream>

using namespace std;

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 540;

bool init();
bool loadmedia();
void close();
void keepWindowOpen();

SDL_Window* window = NULL;
SDL_Surface* windowSurface = NULL;
// Load individual image
SDL_Surface* loadSurface(string url);
SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
// Current displayed image
SDL_Surface* currentSurface = NULL;

SDL_Surface* loadSurface(string path) {
  // TODO: check removing c_str()
  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    cout << "unable to load the image " << SDL_GetError();
  }
  return loadedSurface;
}

int main(int argc, char* args[]) {
  if (!init()) {
    cout << "Failed to init" << endl;
  } else {
    if (!loadmedia()) {
      cout << "failed to load media " << endl;
    } else {
      // init with default service
      if (currentSurface == NULL) {
        currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
      }
      // Apply the image
      SDL_BlitSurface(currentSurface, NULL, windowSurface, NULL);
      SDL_UpdateWindowSurface(window);
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
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_UP:
            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
            cout << "Keydown " << e.key.keysym.sym << "::::" << SDLK_UP << endl;
            break;
          case SDLK_DOWN:
            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
            break;
          default:
            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            break;
        }
        SDL_FillRect(windowSurface, NULL,
                     SDL_MapRGB(windowSurface->format, 0x00, 0x00, 0x00));
        SDL_BlitSurface(currentSurface, NULL, windowSurface, NULL);
        SDL_UpdateWindowSurface(window);
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
    window = SDL_CreateWindow("Slider", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      cout << "Window could not be created! " << SDL_GetError();
      success = false;
    } else {
      windowSurface = SDL_GetWindowSurface(window);
    }
  }

  return success;
}

bool loadmedia() {
  bool success = true;
  // Default surface
  keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] =
      loadSurface("assets/hello_world.bmp");
  if (keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    cout << "Unable to load default image assets/hello_world.bmp "
         << SDL_GetError() << endl;
    success = false;
  }

  keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/up.bmp");
  if (keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    cout << "Unable to load surface up image assets/up.webp " << SDL_GetError()
         << endl;
    success = false;
  }

  keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/down.bmp");
  if (keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    cout << "Unable to load surface down image assets/down.bmp "
         << SDL_GetError() << endl;
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(currentSurface);
  currentSurface = NULL;

  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();
}
