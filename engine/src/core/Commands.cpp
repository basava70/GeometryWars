#include "engine/core/Commands.hpp"
#include "engine/components/Components.hpp"
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>

using namespace engine::core;
using namespace engine::components;

void WalkingUpCommand::execute(entt::registry &registry, entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dx = 0;
    v.dy = -mSpeed;
  }
}
void WalkingDownCommand::execute(entt::registry &registry,
                                 entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dx = 0;
    v.dy = mSpeed;
  }
}
void WalkingRightCommand::execute(entt::registry &registry,
                                  entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dx = mSpeed;
    v.dy = 0;
  }
}
void WalkingLeftCommand::execute(entt::registry &registry,
                                 entt::entity entity) {
  if (registry.any_of<Velocity>(entity)) {
    auto &v = registry.get<Velocity>(entity);
    v.dx = -mSpeed;
    v.dy = 0;
  }
}
