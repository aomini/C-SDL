#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>

#include <cstddef>
#include <iostream>

using namespace std;

class LTexture {
 public:
  // intialize Variables
  LTexture(SDL_Renderer* renderer);

  ~LTexture();

  bool loadFromFile(string path);

  // Deallocate texture
  void free();

  // Set color modulation
  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  // Set blending
  void setBlendMode(SDL_BlendMode blending);

  // Set Alpha modulation
  void setAlpha(Uint8 alpha);

  void render(int x, int y, SDL_Rect* clip = nullptr);

  // Get Dimension
  int getWidth();
  int getHeight();

  // Get renderer
  int getRenderer();

 private:
  SDL_Renderer* mrenderer;
  // The actual hardware texture
  SDL_Texture* mTexture;

  // Dimensions
  int mWidth;
  int mHeight;
};

LTexture::LTexture(SDL_Renderer* renderer) {
  // init
  mTexture = nullptr;
  mWidth = 0;
  mHeight = 0;
  mrenderer = renderer;
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
    finalTexture = SDL_CreateTextureFromSurface(mrenderer, loadedSurface);
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

void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b) {
  SDL_SetTextureColorMod(mTexture, r, g, b);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};
  if (clip != nullptr) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopy(mrenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }
