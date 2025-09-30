#include "engine/core/Commands.hpp"
#include "engine/components/Components.hpp"
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>

using namespace engine::core;
using namespace engine::components;

void MoveUpCommand::execute(entt::registry &registry, entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dy = -mSpeed;
    v.dx = 0;
  }
}
void MoveDownCommand::execute(entt::registry &registry, entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dy = mSpeed;
    v.dx = 0;
  }
}
void MoveRightCommand::execute(entt::registry &registry, entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dx = mSpeed;
    v.dy = 0;
  }
}
void MoveLeftCommand::execute(entt::registry &registry, entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dx = -mSpeed;
    v.dy = 0;
  }
}
