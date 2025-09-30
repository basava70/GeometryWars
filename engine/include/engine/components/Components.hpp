#pragma once

#include "engine/core/Texture.hpp"
#include <SDL3/SDL_rect.h>
#include <cstddef>
#include <memory>
#include <vector>
namespace engine::components {

struct Transform {
  float x{}, y{};          /// cordinates of the object
  float width{}, height{}; /// width and height of the object size
  int degrees{};
};

struct Velocity {
  float dx{}, dy{};
};

struct Renderable {
  std::shared_ptr<engine::core::Texture> mTexture;
  SDL_FRect mSrcRect;
};

struct Animation {
  std::vector<SDL_FRect> frames;
  std::size_t currentFrame{0};
  float frameDuration{0.1f};
  float timer{0.0f};
  bool loop{true};
};
} // namespace engine::components
