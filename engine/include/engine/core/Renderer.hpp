#pragma once
#include "engine/components/Components.hpp"
#include "engine/core/Color.hpp"
#include "engine/core/Texture.hpp"
#include "engine/core/Window.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <memory>

namespace engine::core {
using namespace engine::components;

struct RendererDeleter {
  void operator()(SDL_Renderer *renderer) {
    if (renderer)
      SDL_DestroyRenderer(renderer);
  }
};

class Renderer {
public:
  bool init(Window &);
  void clear(Color color = {0, 0, 0, 255});
  void present();
  SDL_Renderer *get() const;
  void shutdown() noexcept;

  void draw(Renderable const &renderable, Transform const &transform);

  ~Renderer();

private:
  using RendererPtr = std::unique_ptr<SDL_Renderer, RendererDeleter>;
  RendererPtr mRenderer;
};
} // namespace engine::core
