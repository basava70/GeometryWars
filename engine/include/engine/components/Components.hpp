#pragma once

#include "engine/core/Texture.hpp"
#include <SDL3/SDL_rect.h>
#include <memory>
namespace engine::components {

struct Transform {
  float x{}, y{};
  float width{}, height{};
  int degrees{};
};

struct Velocity {
  float dx{}, dy{};
};

struct Renderable {
  std::shared_ptr<engine::core::Texture> mTexture;
  SDL_FRect mSrcRect;
};
} // namespace engine::components
