#include "engine/ecs/EntityManager.hpp"
#include <cassert>

namespace engine::ecs {
EntityManager::EntityManager() {}

Entity EntityManager::createEntity() {
  assert(mCurrEntities < MAX_ENTITIES &&
         "mCurrEntities already are the size of MAX_ENTITIES");

  /// If there are free entities (from destroyed entities) we create
  /// new entity from it
  Entity id;
  if (!mFreeEntities.empty()) {
    id = mFreeEntities.back();
    mFreeEntities.pop_back();
    mCurrEntities++;
  } else {
    id = mNextEntityId++;
  }
  mCurrEntities++;
  mAlive[id] = true;
  return id;
}

void EntityManager::destroyEntity(Entity entity) {
  assert(entity < MAX_ENTITIES && mAlive[entity] && "Invalid entity");
  mAlive[entity] = false;
  mFreeEntities.push_back(entity);
  mCurrEntities--;
  mSignatures[entity].reset();
}

void EntityManager::setSignature(Entity entity, Signature signature) {
  assert(entity < MAX_ENTITIES && mAlive[entity] && "Invalid entity");
  mSignatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity) {
  assert(entity < MAX_ENTITIES && mAlive[entity] && "Invalid entity");
  return mSignatures[entity];
}

} // namespace engine::ecs
