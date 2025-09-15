#include "engine/core/Commands.hpp"
#include "engine/components/Components.hpp"
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>

using namespace engine::core;
using namespace engine::components;

float const SPEED = 200.0f;

void MoveUpCommand::execute(entt::registry &registry, entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dy = -SPEED;
  }
}
void MoveDownCommand::execute(entt::registry &registry, entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dy = SPEED;
  }
}
void MoveRightCommand::execute(entt::registry &registry, entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dx = SPEED;
  }
}
void MoveLeftCommand::execute(entt::registry &registry, entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dx = -SPEED;
  }
}
