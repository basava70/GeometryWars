#pragma once

#include "engine/core/Renderer.hpp"
#include <entt/entity/fwd.hpp>
namespace engine::systems {

void movementSystem(entt::registry &, float);
void renderSystem(entt::registry &, core::Renderer &);

} // namespace engine::systems
