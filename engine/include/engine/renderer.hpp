#pragma once
#include "engine/color.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <memory>

namespace engine {
template <typename T> struct RendererDeleter;

template <> struct RendererDeleter<SDL_Renderer> {
  void operator()(SDL_Renderer *renderer) {
    if (renderer)
      SDL_DestroyRenderer(renderer);
  }
};

using SDLRendererPtr =
    std::unique_ptr<SDL_Renderer, RendererDeleter<SDL_Renderer>>;

class Renderer {
public:
  bool init(SDL_Window *);
  void clear(Color);
  void present();

private:
  SDLRendererPtr mRenderer;
};
} // namespace engine
