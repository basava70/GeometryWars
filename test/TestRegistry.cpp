#include "engine/ecs/EntityManager.hpp"
#include "engine/ecs/Registry.hpp"
#include "engine/ecs/SystemManager.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace engine::ecs;

struct TestIntComponent {
  int x, y;
};
struct TestStringComponent {
  std::string name;
};

struct TestFloatComponent {
  float dx, dy;
};

struct TestSystem : public ISystem {
  void update(float dt) override {}
};

TEST_CASE("Registry", "[ECS]") {

  Registry registry;

  SECTION("Create entity") {
    Entity sqaure = registry.createEntity();
    Entity rectangle = registry.createEntity();
    REQUIRE(sqaure != rectangle);
  }
}
