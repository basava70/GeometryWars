#include "engine/rect.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <memory>

namespace engine {

template <typename T> struct TextureDeleter;

template <> struct TextureDeleter<SDL_Texture> {
  void operator()(SDL_Texture *texture) {
    if (texture)
      SDL_DestroyTexture(texture);
  }
};
template <typename T> using TexturePtr = std::unique_ptr<T, TextureDeleter<T>>;

struct Texture {
  Texture(std::string const &path);
  Texture(SDL_Surface *);
  SDL_Texture *get() const;
  TexturePtr<SDL_Texture> mTexture;
  RectF mRect;
};
} // namespace engine
