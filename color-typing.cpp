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

class LTexture {
 public:
  // intialize Variables
  LTexture();

  ~LTexture();

  bool loadFromFile(string path);

  // Deallocate texture
  void free();

  void render(int x, int y);

  // Get Dimension
  int getWidth();
  int getHeight();

 private:
  // The actual hardware texture
  SDL_Texture* mTexture;

  // Dimensions
  int mWidth;
  int mHeight;
};

LTexture::LTexture() {
  // init
  mTexture = nullptr;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() { free(); }

bool LTexture::loadFromFile(string path) {
  // Get Rid of preexisting texture
  free();

  SDL_Texture* finalTexture = nullptr;
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    cout << "Unable to load image! SDL_Error " << SDL_GetError() << endl;
    return false;
  } else {
    cout << "Pixel Format: "
         << SDL_GetPixelFormatName(loadedSurface->format->format) << endl;
    // color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0x00));
    finalTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (finalTexture == nullptr) {
      cout << "Unable to create texture! SDL_Error: " << SDL_GetError() << endl;
      return false;
    } else {
      // Get image dimensions
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }
    SDL_FreeSurface(loadedSurface);
  }
  mTexture = finalTexture;
  return true;
}

void LTexture::free() {
  if (mTexture != nullptr) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::render(int x, int y) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};
  SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }

// Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;

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

bool loadMedia() {
  // Loading success flag
  bool success = true;

  if (!gFooTexture.loadFromFile("assets/foo.png")) {
    cout << "Failed to load foo" << endl;
    success = false;
  }
  if (!gBackgroundTexture.loadFromFile("assets/background.png")) {
    cout << "Failed to load backgorund" << endl;
    success = false;
  }
  return success;
}

void close() {
  gFooTexture.free();
  gBackgroundTexture.free();

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

    gBackgroundTexture.render(0, 0);

    gFooTexture.render(240, 190);

    SDL_RenderPresent(renderer);
  }
}

int main() {
  if (!init()) {
    cout << "SDL could not be initialized" << endl;
  } else {
    // Draw
    loadMedia();
    keepWindowOpen();
  }
  close();
  return EXIT_SUCCESS;
}
