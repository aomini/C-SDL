#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>

#include <string>
using namespace std;

#ifndef LTexture_h
#define LTexture_h

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
#endif
