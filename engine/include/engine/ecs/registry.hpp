#pragma once

#include "engine/ecs/entity.hpp"

namespace engine::ecs {
class Registry {
public:
  Entity create();

  template <typename Component, typename... Args>
  void assign(Entity e, Args &&...args);

  template <typename Component> Component &get(Entity e);

  template <typename... Components> auto view();
};

} // namespace engine::ecs
