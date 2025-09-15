#include "engine/core/Texture.hpp"
#include "engine/core/Renderer.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <string>

namespace engine::core {

bool Texture::loadFromFile(Renderer const &renderer, std::string const &path) {
  SDL_Texture *raw = IMG_LoadTexture(renderer.get(), path.c_str());
  if (!raw) {
    SDL_Log("Failed to load texture '%s' : %s", path.c_str(), SDL_GetError());
    return false;
  }
  mTexture.reset(raw);
  mWidth = mTexture->w;
  mHeight = mTexture->h;
  return true;
}

} // namespace engine::core
