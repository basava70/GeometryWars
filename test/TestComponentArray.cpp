#include "engine/ecs/ComponentManager.hpp"
#include "engine/ecs/Entity.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("ComponenetArray", "[ECS]") {
  engine::ecs::ComponentArray<std::string> compArray;

  SECTION("Add entities and retrieve respective componenets") {
    compArray.add(1, "first");
    compArray.add(2, "second");
    compArray.add(3, "third");
    auto c = compArray.getComponent(2);
    REQUIRE(c != nullptr);
    REQUIRE(*c == "second");
  }
}
