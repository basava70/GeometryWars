#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <memory>

namespace engine {

struct TextureDeleter {
  void operator()(SDL_Texture *texture) {
    if (texture)
      SDL_DestroyTexture(texture);
  }
};
using TexturePtr = std::unique_ptr<SDL_Texture, TextureDeleter>;

class Texture {
public:
private:
  TexturePtr mTexture;
};
} // namespace engine
