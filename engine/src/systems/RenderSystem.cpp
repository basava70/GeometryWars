#include "engine/components/Components.hpp"
#include "engine/core/Renderer.hpp"
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>

namespace engine::systems {
using namespace engine::core;
using namespace engine::components;

void renderSystem(entt::registry &registry, Renderer &renderer) {

  auto view = registry.view<Transform, Renderable>();

  for (auto entity : view) {
    auto &t = view.get<Transform>(entity);
    auto &r = view.get<Renderable>(entity);

    renderer.draw(r, t);
  }
}

} // namespace engine::systems
