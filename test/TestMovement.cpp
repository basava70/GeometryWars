#include "engine/components/Components.hpp"
#include "engine/systems/systems.hpp"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <entt/entt.hpp>

using namespace engine::components;
using namespace engine::systems;

TEST_CASE("Movement system updates Transform position correctly",
          "[movement]") {
  entt::registry registry;
  auto entity = registry.create();

  registry.emplace<Transform>(entity, 0.0f, 0.0f, 10.0f, 10.0f, 0.0f);
  registry.emplace<Velocity>(entity, 5.0f, 0.0f);

  double dt = 1.0; // 1 second
  movementSystem(registry, dt);

  const auto &transform = registry.get<Transform>(entity);

  REQUIRE(transform.x == Catch::Approx(5.0f));
  REQUIRE(transform.y == Catch::Approx(0.0f));
}
