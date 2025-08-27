#include "engine/ecs/Entity.hpp"

namespace engine::ecs {

Entity EntityManager::CreateEntity() {
  if (!mFreeEntities.empty()) {
    Entity id = mFreeEntities.back();
    mFreeEntities.pop_back();
    return id;
  }
  return mNextEntityId++;
}

void EntityManager::DestroyEntity(Entity entity) {
  mFreeEntities.push_back(entity);
}

} // namespace engine::ecs
