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

  void render(int x, int y, SDL_Rect* clip = nullptr);

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

void LTexture::render(int x, int y, SDL_Rect* clip) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};
  if (clip != nullptr) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }

// Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
const int JUMP_ANIMATION_FRAMES = 5;
// Sprite scenes
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
SDL_Rect gJumpClips[JUMP_ANIMATION_FRAMES];

LTexture gSpriteTexture;
LTexture gbackground;

bool init() {
  bool success = true;

  // initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize " << SDL_GetError() << endl;
    success = false;
  } else {
    // create window
    gWindow = SDL_CreateWindow("Naruto Game", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      cout << "Window couldnot be created " << SDL_GetError() << endl;
      success = false;
    } else {
      renderer = SDL_CreateRenderer(
          gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

  if (!gSpriteTexture.loadFromFile("assets/naruto-sprite.png")) {
    cout << "Failed to load sprite image" << endl;
    success = false;
  } else {
    // First stance
    gSpriteClips[0].x = 5;
    gSpriteClips[0].y = 270;
    gSpriteClips[0].w = 60;
    gSpriteClips[0].h = 60;

    // Top right sprite
    gSpriteClips[1].x = 60;
    gSpriteClips[1].y = 270;
    gSpriteClips[1].w = 60;
    gSpriteClips[1].h = 60;

    // Bottom left sprite
    gSpriteClips[2].x = 120;
    gSpriteClips[2].y = 270;
    gSpriteClips[2].w = 50;
    gSpriteClips[2].h = 60;

    // Bottom right sprite
    gSpriteClips[3].x = 175;
    gSpriteClips[3].y = 270;
    gSpriteClips[3].w = 50;
    gSpriteClips[3].h = 60;

    // JUMPING SPRITES
    gJumpClips[0].x = 19;
    gJumpClips[0].y = 429;
    gJumpClips[0].w = 45;
    gJumpClips[0].h = 63;

    gJumpClips[1].x = 64;
    gJumpClips[1].y = 429;
    gJumpClips[1].w = 48;
    gJumpClips[1].h = 63;

    gJumpClips[2].x = 112;
    gJumpClips[2].y = 429;
    gJumpClips[2].w = 49;
    gJumpClips[2].h = 63;

    gJumpClips[3].x = 161;
    gJumpClips[3].y = 429;
    gJumpClips[3].w = 48;
    gJumpClips[3].h = 63;

    gJumpClips[4].x = 209;
    gJumpClips[4].y = 429;
    gJumpClips[4].w = 51;
    gJumpClips[4].h = 63;
  }

  // Jump character

  // bg
  if (!gbackground.loadFromFile("assets/konoha.jpg")) {
    cout << "Failed to load background" << endl;
    success = false;
  }

  return success;
}

void close() {
  gSpriteTexture.free();

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

  // Current animation frame
  int frame = 0;

  // Frame delay control
  float frameDelay = 18;  // Delay in frames before switching to the next sprite
  int frameCount = 0;     // Counts frames to apply the delay

  // Jump parameters
  int baseY = (SCREEN_HEIGHT - gJumpClips[0].h) / 2;  // Ground position
  int posY = baseY;                                   // Current Y position
  float velocityY = -5.0f;  // Initial jump velocity (upward)
  float gravity = 0.2f;     // Gravity acceleration
  bool jumping = false;

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }

      // Start the jump when pressing space
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !jumping) {
        jumping = true;
        velocityY = -5.0f;  // Reset jump velocity
      }
    }

    // Clear Screen
    SDL_SetRenderDrawColor(renderer, 0x31, 0x33, 0x40, 0xFF);
    SDL_RenderClear(renderer);

    // Render the background
    SDL_Rect backgroundClip = {0, 200, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    gbackground.render(0, 0, &backgroundClip);

    // Jump animation and vertical movement
    if (jumping) {
      posY += velocityY;     // Update position based on velocity
      velocityY += gravity;  // Apply gravity

      // If character lands back on the ground, stop the jump
      if (posY >= baseY) {
        posY = baseY;  // Reset position to ground
        jumping = false;
        velocityY = 0;   // Reset velocity
        frame = 0;       // Reset animation frame
        frameCount = 0;  // Reset frame delay
      }
    }

    // Apply frame delay to slow down animation
    if (frameCount >= frameDelay) {
      ++frame;         // Move to the next animation frame
      frameCount = 0;  // Reset frame count
    } else {
      ++frameCount;  // Increment frame count
    }

    // Select the current sprite frame
    SDL_Rect* jumpClip =
        &gJumpClips[frame % JUMP_ANIMATION_FRAMES];  // Loop frames
    gSpriteTexture.render((SCREEN_WIDTH - jumpClip->w) / 2, posY, jumpClip);

    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(16);  // ~60 FPS
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
