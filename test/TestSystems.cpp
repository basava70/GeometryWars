#include "engine/ecs/EntityManager.hpp"
#include "engine/ecs/SystemManager.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace engine::ecs;

class DummySystem : public ISystem {
public:
  void update(float dt) override {}
};

TEST_CASE("SystemManager", "[ECS]") {
  SystemManager systemManager;

  SECTION("Register and retrieve system") {
    systemManager.registerSystem<DummySystem>();
    auto dummy = systemManager.getSystem<DummySystem>();
    REQUIRE(dummy);
  }

  SECTION("Set the Signature to match the Entity") {
    Signature sig = 0b0101;
    Entity entity = 1;

    systemManager.registerSystem<DummySystem>();
    systemManager.SetSignature<DummySystem>(sig);
    systemManager.entitySignatureChanged(entity, sig);
    // check if entity "1" is present in DummySystem
    auto dummy = systemManager.getSystem<DummySystem>();
    REQUIRE(dummy->mEntitySet.contains(entity));

    // now we change entity signature to confirm entity is removed
    Signature changedSig = 0b0010;
    systemManager.entitySignatureChanged(entity, changedSig);
    REQUIRE(!dummy->mEntitySet.contains(entity));
  }

  SECTION("Signatures doesnt match") {
    Signature systemSig = 0b111;
    Signature entitySig = 0b010;
    systemManager.registerSystem<DummySystem>();
    systemManager.SetSignature<DummySystem>(systemSig);
    Entity entity = 1;
    systemManager.entitySignatureChanged(entity, entitySig);
    // entity shouldnt be in dummy system
    auto dummy = systemManager.getSystem<DummySystem>();
    REQUIRE(!dummy->mEntitySet.contains(entity));
  }
}
