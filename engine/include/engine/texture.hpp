#include <SDL3/SDL.h>
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

class Texture {
public:
private:
  TexturePtr<SDL_Texture> mTexture;
};
} // namespace engine
