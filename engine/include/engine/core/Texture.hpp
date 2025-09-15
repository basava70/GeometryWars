#pragma once

#include <SDL3/SDL.h>
#include <memory>

namespace engine::core {
class Renderer;

template <typename T> struct TextureDeleter;

template <> struct TextureDeleter<SDL_Texture> {
  void operator()(SDL_Texture *texture) {
    if (texture)
      SDL_DestroyTexture(texture);
  }
};

using SDLTexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter<SDL_Texture>>;

class Texture {
public:
  Texture() = default;

  Texture(Texture const &) = delete;
  Texture &operator=(Texture const &) = delete;

  Texture(Texture &&) noexcept = default;
  Texture &operator=(Texture &&) noexcept = default;

  bool loadFromFile(Renderer const &renderer, std::string const &path);

  int width() const { return mWidth; }
  int height() const { return mHeight; }

  SDL_Texture *get() const { return mTexture.get(); }

private:
  SDLTexturePtr mTexture;
  int mWidth{0};
  int mHeight{0};
};

} // namespace engine::core
