#include "engine/core/Renderer.hpp"
#include "engine/components/Components.hpp"
#include "engine/core/Texture.hpp"
#include "engine/core/Window.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <cmath>

namespace engine::core {
using namespace engine::components;

bool Renderer::init(Window &window, int width, int height) {
  SDL_Renderer *raw = SDL_CreateRenderer(window.get(), 0);
  if (!raw) {
    SDL_Log("Error creating Renderer: %s", SDL_GetError());
    return false;
  }
  SDL_SetRenderLogicalPresentation(raw, width, height,
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
  // SDL_FRect dst{std::round(transform.x), std::round(transform.y),
  //               transform.width, transform.height};
  SDL_FRect dst{(transform.x), (transform.y), transform.width,
                transform.height};

  SDL_Log("src = {%.2f, %.2f, %.2f, %.2f}, dst = {%.2f, %.2f, %.2f, %.2f}",
          renderable.mSrcRect.x, renderable.mSrcRect.y, renderable.mSrcRect.w,
          renderable.mSrcRect.h, dst.x, dst.y, dst.w, dst.h);
  SDL_RenderTexture(mRenderer.get(), renderable.mTexture->get(),
                    &renderable.mSrcRect, &dst);
}

Renderer::~Renderer() { shutdown(); }

} // namespace engine::core
