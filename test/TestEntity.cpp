#include "engine/ecs/EntityManager.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace engine::ecs;

TEST_CASE("EntityManager", "[ECS]") {
  EntityManager entityManager;

  SECTION("Create entity") {
    Entity e1 = entityManager.createEntity();
    Entity e2 = entityManager.createEntity();
    REQUIRE(e1 != e2);
  }

  SECTION("Set signature") {
    Entity e1 = entityManager.createEntity();

    Signature sig1 = 0b0111;
    entityManager.setSignature(e1, sig1);
    Entity e2 = entityManager.createEntity();
    Signature sig2 = 0b1010;
    entityManager.setSignature(e2, sig2);

    Signature testSig1 = entityManager.getSignature(e1);
    Signature testSig2 = entityManager.getSignature(e2);
    REQUIRE(testSig1 == sig1);
    REQUIRE(testSig2 == sig2);
  }

  SECTION("Destroy Entity") {
    Entity e1 = entityManager.createEntity();

    Signature sig1 = 0b0111;
    entityManager.setSignature(e1, sig1);
    Entity e2 = entityManager.createEntity();
    Signature sig2 = 0b1010;
    entityManager.setSignature(e2, sig2);

    entityManager.destroyEntity(e1);
    // auto testSig1 = entityManager.getSignature(e1);
    // REQUIRE(testSig1 == false);
    auto testSig2 = entityManager.getSignature(e2);
    REQUIRE(testSig2 == sig2);
    entityManager.destroyEntity(e2);
    // testSig2 = entityManager.getSignature(e2);
    // REQUIRE(testSig2 == false);
  }
}
