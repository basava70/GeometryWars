#pragma once
#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace engine::ecs {

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;
static constexpr ComponentType MAX_COMPONENTS = 64;
using Signature = std::bitset<MAX_COMPONENTS>;
// TODO: change MAX_ENTITIES to 5000 later
static constexpr std::size_t MAX_ENTITIES = 7;

class EntityManager {
public:
  EntityManager();
  Entity createEntity();
  void destroyEntity(Entity entity);
  void setSignature(Entity entity, Signature signature);
  Signature getSignature(Entity entity);

private:
  Entity mNextEntityId{0};
  std::vector<Entity> mFreeEntities;
  std::array<Signature, MAX_ENTITIES> mSignatures;
  std::size_t mCurrEntities{0};
  std::array<bool, MAX_ENTITIES> mAlive{};
};

} // namespace engine::ecs
