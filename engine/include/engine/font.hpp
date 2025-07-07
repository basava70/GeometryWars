#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

/**
 * \brief Manages the font for the engine
 *
 * Currently implemented using SDL3_TTF
 */
class Font {
public:
  bool init(std::string const &path, std::size_t fontSize = 14);
  SDL_Surface *createSurfaceBlended(std::string const &text, SDL_Color);
  ~Font();

private:
  TTF_Font *mFont{nullptr};
};
