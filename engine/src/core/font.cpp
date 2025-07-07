#include "engine/font.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <print>

bool Font::init(std::string const &path, std::size_t fontSize) {
  if (!TTF_Init()) {
    std::println("Error initializing TTF: {}", SDL_GetError());
    return false;
  }
  mFont = TTF_OpenFont(path.c_str(), fontSize);
  if (!mFont) {
    std::println("Error loading font: {}", SDL_GetError());
    return false;
  }
  return true;
}

SDL_Surface *Font::createSurfaceBlended(std::string const &text,
                                        SDL_Color color) {
  return TTF_RenderText_Blended(mFont, text.c_str(), 0, color);
}

Font::~Font() {
  if (mFont) {
    TTF_CloseFont(mFont);
  }
  TTF_Quit();
}
