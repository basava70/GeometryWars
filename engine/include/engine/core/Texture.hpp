#pragma once

#include "engine/core/Rect.hpp"
#include <SDL3/SDL.h>
#include <memory>

namespace engine::core {

template <typename T> struct TextureDeleter;

template <> struct TextureDeleter<SDL_Texture> {
  void operator()(SDL_Texture *texture) {
    if (texture)
      SDL_DestroyTexture(texture);
  }
};

using SDLTexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter<SDL_Texture>>;

struct Texture {
  Texture(Texture const &) = delete;
  Texture &operator=(Texture const &) = delete;
  Texture(Texture &&) noexcept = delete;
  Texture &operator=(Texture &&) noexcept = delete;

  RectF getRect() const;

  template <typename T> T *get() const;

  SDLTexturePtr mTexture;
  RectF mRect;
};

} // namespace engine::core
