#pragma once
#include "engine/color.hpp"
#include "engine/rect.hpp"
namespace engine::components {

struct Sprite {

  engine::RectF rect;
  engine::Color color;
};
} // namespace engine::components
