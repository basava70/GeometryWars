#include "engine/components/Components.hpp"
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>

namespace engine::systems {
using namespace engine::components;

void movementSystem(entt::registry &registry, float dt) {

  auto view = registry.view<Transform, Velocity>();
  for (auto entity : view) {
    auto &t = view.get<Transform>(entity);
    auto &v = view.get<Velocity>(entity);
    t.x += v.dx * dt;
    t.y += v.dy * dt;
  }
}

} // namespace engine::systems
