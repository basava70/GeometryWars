#include "engine/renderer.hpp"
#include <print>

namespace engine {

bool Renderer::init(SDL_Window *window) {
  SDL_Renderer *raw = SDL_CreateRenderer(window, 0);
  if (!raw) {
    std::println("Error creating Renderer {}", SDL_GetError());
    return false;
  }
  mRenderer.reset(raw);
  return true;
}

SDL_Renderer *Renderer::get() const { return mRenderer.get(); }

void Renderer::clear(Color color) {
  SDL_SetRenderDrawColor(get(), color.r, color.g, color.b, color.a);
  SDL_RenderClear(get());
}

void Renderer::present() { SDL_RenderPresent(get()); }

void Renderer::shutdown() noexcept { mRenderer.reset(); }

Renderer::~Renderer() { shutdown(); }

} // namespace engine
