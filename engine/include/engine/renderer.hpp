#pragma once
#include "engine/color.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <memory>

namespace engine {

struct RendererDeleter {
  void operator()(SDL_Renderer *renderer) {
    if (renderer)
      SDL_DestroyRenderer(renderer);
  }
};

using RendererPtr = std::unique_ptr<SDL_Renderer, RendererDeleter>;

class Renderer {
public:
  bool init(SDL_Window *);
  void clear(Color color = {0, 0, 0, 255});
  void present();
  SDL_Renderer *get() const;
  void shutdown() noexcept;

  ~Renderer();

private:
  RendererPtr mRenderer;
};
} // namespace engine
