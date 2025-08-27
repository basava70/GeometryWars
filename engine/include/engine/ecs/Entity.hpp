#pragma once
#include <cstdint>
#include <vector>
namespace engine::ecs {

using Entity = std::uint32_t;
static constexpr std::size_t MAX_ENTITIES = 7;

class EntityManager {
public:
  Entity CreateEntity();
  void DestroyEntity(Entity entity);

private:
  Entity mNextEntityId{0};
  std::vector<Entity> mFreeEntities;
};

} // namespace engine::ecs
