#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

#include "src/LTexture.h"

using namespace std;

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 680;

SDL_Window* gWindow;
SDL_Renderer* gRenderer = nullptr;

bool init();

int main() {
  if (!init()) {
    cout << "Unable to init SDL" << endl;
    return EXIT_FAILURE;
  }

  LTexture gArrowTexture(gRenderer);
  if (!gArrowTexture.loadFromFile("assets/arrow.png")) {
    cout << "Arrow.png couldn't be loaded at the moment! SDL_Error! "
         << SDL_GetError() << endl;
    return EXIT_FAILURE;
  }

  // main loop flag
  bool quit = false;
  SDL_Event e;
  double degrees = 0;

  // Flip type
  SDL_RendererFlip flipType = SDL_FLIP_NONE;

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_a:
            degrees -= 60;
            break;
          case SDLK_d:
            degrees += 60;
            break;
          case SDLK_q:
            flipType = SDL_FLIP_HORIZONTAL;
            break;
          case SDLK_w:
            flipType = SDL_FLIP_NONE;
            break;
          case SDLK_e:
            flipType = SDL_FLIP_VERTICAL;
            break;
        }
      }
    }
    // Set Color bg
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(gRenderer);

    // Render Arrow:
    gArrowTexture.render((SCREEN_WIDTH - gArrowTexture.getWidth()) / 2,
                         (SCREEN_HEIGHT - gArrowTexture.getHeight()) / 2, NULL,
                         true, degrees, NULL, flipType);

    SDL_RenderPresent(gRenderer);
  }

  return EXIT_SUCCESS;
}
bool init() {
  bool success = true;

  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize " << SDL_GetError() << endl;
    success = false;
  } else {
    // create window
    gWindow = SDL_CreateWindow("Rotatation & flip with renderEx",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      cout << "Window couldnot be created " << SDL_GetError() << endl;
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(
          gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
        cout << "Renderer could not be created: SDL_Error: " << SDL_GetError()
             << endl;
        success = false;
      } else {
        // Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 0XEF, 0XB0, 0x36, 0xFF);
        // init PNG loading
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
          cout << "SDL image could not be initialize! SDL_image error "
               << SDL_GetError() << endl;
          success = false;
        }
      }
    }
  }
  return success;
}
