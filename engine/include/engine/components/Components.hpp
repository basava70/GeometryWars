#pragma once

#include "engine/core/Texture.hpp"
#include <SDL3/SDL_rect.h>
#include <memory>
#include <unordered_map>
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

enum class AnimationState {
  Idle,
  Walk,
  Run,
  Jump,
  Attack1,
  Attack2,
  Attack3,
  Hurt,
  Dead,
  Shield
};

struct AnimationFrames {
  std::vector<SDL_FRect> mFrames;
  float mFrameDuration{0.1f};
  bool loop{true};
};

struct Animation {
  std::unordered_map<AnimationState, AnimationFrames> mAnimations;
};

} // namespace engine::components
