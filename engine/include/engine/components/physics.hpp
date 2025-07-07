#pragma once

namespace engine::components {

struct Transform {
  float x = 0.0f;
  float y = 0.0f;
};

struct Velocity {
  float dx = 0.0f;
  float dy = 0.0f;
};

} // namespace engine::components
