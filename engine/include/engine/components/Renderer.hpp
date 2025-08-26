#pragma once
#include "engine/Color.hpp"
#include "engine/Rect.hpp"
namespace engine::components {

struct RenderComponent {

  engine::RectF rect;
  engine::Color color;
};
} // namespace engine::components
