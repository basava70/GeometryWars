#include "engine/ecs/ComponentManager.hpp"
#include "engine/ecs/Entity.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("ComponenetArray", "[ECS]") {
  engine::ecs::ComponentArray<std::string> compArray;
  compArray.addComponentDataImpl(1, "one");
  compArray.addComponentDataImpl(2, "two");
  compArray.addComponentDataImpl(3, "three");
  compArray.addComponentDataImpl(4, "four");
  compArray.addComponentDataImpl(5, "five");

  SECTION("Remove first, last and middle elements") {
    compArray.removeComponentDataImpl(1);
    auto c = compArray.getComponentDataImpl(5);
    REQUIRE(c == "five");

    compArray.removeComponentDataImpl(4);
    c = compArray.getComponentDataImpl(2);
    REQUIRE(c == "two");

    compArray.removeComponentDataImpl(2);
    c = compArray.getComponentDataImpl(3);
    REQUIRE(c == "three");

    c = compArray.getComponentDataImpl(5);
    REQUIRE(c == "five");
  }

  SECTION("Add removed first entity") {
    compArray.removeComponentDataImpl(1);
    compArray.addComponentDataImpl(1, "first");
    auto c = compArray.getComponentDataImpl(1);
    REQUIRE(c == "first");
  }

  SECTION("Add removed last entity") {
    compArray.removeComponentDataImpl(5);
    compArray.addComponentDataImpl(5, "fifth");
    auto c = compArray.getComponentDataImpl(5);
    REQUIRE(c == "fifth");

    // middle entity
    compArray.removeComponentDataImpl(3);
    compArray.addComponentDataImpl(3, "third");
    c = compArray.getComponentDataImpl(3);
    REQUIRE(c == "third");
  }
}

TEST_CASE("ComponentManager", "[ECS]") {
  engine::ecs::ComponentManager compManager;

  engine::ecs::EntityManager entityManager;
  engine::ecs::Entity first = entityManager.CreateEntity();
  engine::ecs::Entity second = entityManager.CreateEntity();
  engine::ecs::Entity third = entityManager.CreateEntity();
  engine::ecs::Entity fourth = entityManager.CreateEntity();
  engine::ecs::Entity fifth = entityManager.CreateEntity();
  engine::ecs::Entity sixth = entityManager.CreateEntity();

  compManager.registerComponent<std::string>();
  compManager.registerComponent<int>();
  compManager.registerComponent<float>();
  // compManager.registerComponent<float>(); // should fail

  compManager.addComponentData<std::string>(first, "first");
  compManager.addComponentData<float>(first, 1.5);
  compManager.addComponentData<std::string>(second, "second");
  compManager.addComponentData<float>(second, 2.5);
  compManager.addComponentData<int>(second, 2);
  compManager.addComponentData<int>(third, 3);
  compManager.addComponentData<float>(fourth, 4.5);
  compManager.addComponentData<std::string>(sixth, "sixth");

  SECTION("Get the components") {
    auto c_str = compManager.getComponentData<std::string>(first);
    REQUIRE(c_str == "first");
    auto c_int = compManager.getComponentData<int>(second);
    REQUIRE(c_int == 2);
    auto c_float = compManager.getComponentData<float>(fourth);
    REQUIRE(c_float == 4.5);
    // should assert
    // c_float = compManager.getComponentData<float>(sixth);

    compManager.removeComponentData<std::string>(first);
    // should assert
    // c_str = compManager.getComponentData<std::string>(first);

    compManager.addComponentData<std::string>(first, "one");
    // should assert
    // compManager.addComponentData<float>(first, 1.6);
    c_str = compManager.getComponentData<std::string>(first);
    REQUIRE(c_str == "one");
    c_float = compManager.getComponentData<float>(first);
    REQUIRE(c_float == 1.5);
  }
}
