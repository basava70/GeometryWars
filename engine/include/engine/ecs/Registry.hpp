#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include <memory>

namespace engine::ecs {

class Registry {

public:
  Registry()
      : mComponentManger(std::make_unique<ComponentManager>()),
        mSystemManager(std::make_unique<SystemManager>()),
        mEntityManager(std::make_unique<EntityManager>()) {}

  Entity createEntity() { return mEntityManager->createEntity(); }

  void destroyEntity(Entity entity) {
    mEntityManager->destroyEntity(entity);
    mComponentManger->entityDestroyed(entity);
    mSystemManager->entityDestroyed(entity);
  }

  template <typename T> void registerComponent() {
    mComponentManger->registerComponent<T>();
  }

  template <typename T> void addComponentToEntity(Entity entity, T component) {
    mComponentManger->addComponentData(entity, component);
    auto signature = mEntityManager->getSignature(entity);
    signature.set(mComponentManger->getComponentType<T>(), true);

    mEntityManager->setSignature(entity, signature);
    mSystemManager->entitySignatureChanged(entity, signature);
  }

  template <typename T> void removeComponentFromEntity(Entity entity) {
    mComponentManger->removeComponentData<T>(entity);

    auto signature = mEntityManager->getSignature(entity);
    signature.set(mComponentManger->getComponentType<T>(), false);
    mEntityManager->setSignature(entity, signature);
    mSystemManager->entitySignatureChanged(entity, signature);
  }

  template <typename T> T &getComponentFromEntity(Entity entity) {
    return mComponentManger->getComponentData<T>(entity);
  }

  template <typename T> ComponentType getComponenetType() {
    return mComponentManger->getComponentType<T>();
  }

  template <typename T> void registerSystem() {
    mSystemManager->registerSystem<T>();
  }

  template <typename T> std::shared_ptr<ISystem> getSystem() {
    return mSystemManager->getSystem<T>();
  }

  template <typename T> void setSystemSignature(Signature sig) {
    mSystemManager->SetSignature<T>(sig);
  }

private:
  std::unique_ptr<ComponentManager> mComponentManger;
  std::unique_ptr<SystemManager> mSystemManager;
  std::unique_ptr<EntityManager> mEntityManager;
};

} // namespace engine::ecs
