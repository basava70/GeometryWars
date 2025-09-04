#include "engine/ecs/Entity.hpp"
#include <cassert>

namespace engine::ecs {

Entity EntityManager::createEntity() {
  assert(mCurrEntities < MAX_ENTITIES &&
         "mCurrEntities already are the size of MAX_ENTITIES");

  /// If there are free entities (from destroyed entities) we create
  /// new entity from it
  if (!mFreeEntities.empty()) {
    Entity id = mFreeEntities.back();
    mFreeEntities.pop_back();
    mCurrEntities++;
    return id;
  }
  mCurrEntities++;
  return mNextEntityId++;
}

void EntityManager::destroyEntity(Entity entity) {
  assert(entity < MAX_ENTITIES && "entity is out of bounds");
  mFreeEntities.push_back(entity);
  mCurrEntities--;
  mSignatures[entity].reset();
}

void EntityManager::setSignature(Entity entity, Signature signature) {
  assert(entity < MAX_ENTITIES && "entity is out of bounds");
  mSignatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity) {
  assert(entity < MAX_ENTITIES && "entity is out of bounds");
  return mSignatures[entity];
}

} // namespace engine::ecs
