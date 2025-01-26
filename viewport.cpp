#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include <cstddef>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 540;

SDL_Window* gWindow = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* currentTexture = NULL;

bool init();
SDL_Texture* loadTexture(string path);
bool loadMedia();

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
      renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (renderer == NULL) {
        cout << "Renderer could not be created: SDL_Error: " << SDL_GetError()
             << endl;
        success = false;
      } else {
        // Initialize renderer color
        SDL_SetRenderDrawColor(renderer, 0XEF, 0XB0, 0x36, 0xFF);
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

SDL_Texture* loadTexture(string path) {
  // Final texture
  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = IMG_Load(path.c_str());

  if (loadedSurface == NULL) {
    cout << "Unable to load the image! SDL_Error! " << SDL_GetError() << endl;
  } else {
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL) {
      cout << "Unable to create texture from " << path.c_str() << SDL_GetError()
           << endl;
    }
    SDL_FreeSurface(loadedSurface);
  }
  return newTexture;
}

bool loadMedia(string path) {
  bool success = true;
  currentTexture = loadTexture(path);
  if (currentTexture == NULL) {
    cout << "Could not load texture hora?? " << SDL_GetError() << endl;
    success = false;
  }
  return success;
}

void close() {
  SDL_DestroyTexture(currentTexture);
  currentTexture = NULL;

  SDL_DestroyRenderer(renderer);
  renderer = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  IMG_Quit();
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

    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0XFF, 0XFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Top left corner viewport
    loadMedia("assets/spider.png");
    SDL_Rect topLeftViewport = {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    SDL_RenderSetViewport(renderer, &topLeftViewport);
    SDL_RenderCopy(renderer, currentTexture, NULL, NULL);

    // Top right corner viewport
    loadMedia("assets/signature.png");
    SDL_Rect topRight = {SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2,
                         SCREEN_HEIGHT / 2};
    SDL_RenderSetViewport(renderer, &topRight);
    SDL_RenderCopy(renderer, currentTexture, NULL, NULL);

    // Top right corner viewport
    loadMedia("assets/insta.jpg");
    SDL_Rect bottom = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderSetViewport(renderer, &bottom);
    SDL_RenderCopy(renderer, currentTexture, NULL, NULL);

    SDL_RenderPresent(renderer);
  }
}

int main() {
  if (!init()) {
    cout << "SDL could not be initialized" << endl;
  } else {
    // Draw

    keepWindowOpen();
  }
  close();
  return EXIT_SUCCESS;
}
