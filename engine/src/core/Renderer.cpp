#include "engine/core/Renderer.hpp"
#include "engine/components/Components.hpp"
#include "engine/core/Texture.hpp"
#include "engine/core/Window.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

namespace engine::core {
using namespace engine::components;

bool Renderer::init(Window &window) {
  SDL_Renderer *raw = SDL_CreateRenderer(window.get(), 0);
  if (!raw) {
    SDL_Log("Error creating Renderer: %s", SDL_GetError());
    return false;
  }
  SDL_SetRenderLogicalPresentation(raw, window.getWidth(), window.getHeight(),
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);
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

void Renderer::draw(Renderable const &renderable, Transform const &transform) {

  SDL_FRect dst{transform.x - transform.width / 2,
                transform.y - transform.height / 2, transform.width,
                transform.height};

  SDL_RenderTexture(mRenderer.get(), renderable.mTexture->get(),
                    &renderable.mSrcRect, &dst);
}

Renderer::~Renderer() { shutdown(); }

} // namespace engine::core
