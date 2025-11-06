#include "engine/components/Components.hpp"
#include "engine/core/Commands.hpp"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <entt/entt.hpp>

using namespace engine::core;
using namespace engine::components;

TEST_CASE("WalkingLeftCommand applies negative X velocity", "[commands]") {
  entt::registry registry;
  auto player = registry.create();
  registry.emplace<Velocity>(player, 0.f, 0.f);

  WalkingLeftCommand walkLeft(100.0f);
  walkLeft.execute(registry, player);

  auto &vel = registry.get<Velocity>(player);
  REQUIRE(vel.dx < 0.f);
  REQUIRE(std::abs(vel.dx) == Catch::Approx(100.f));
}
