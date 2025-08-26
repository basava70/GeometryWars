#pragma once

namespace engine::components {

struct PositionComponent {
  float x = 0.0f;
  float y = 0.0f;
};

struct VelocityComponent {
  float dx = 0.0f;
  float dy = 0.0f;
};

} // namespace engine::components
