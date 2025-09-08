#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
#include <memory>

namespace engine::ecs {

class Registry {

public:
  Entity CreateEntity() { return mEntityManager->createEntity(); }

  template <typename T> void registerComponent() {
    mComponentManger->registerComponent<T>();
  }

  template <typename T> void addComponentToEntity(Entity entity, T component) {
    mComponentManger->addComponentData(entity, component);
    auto signature = mEntityManager->getSignature(entity);
    signature.set(mComponentManger->getComponentType<T>(), true);

    mEntityManager->setSignature(entity, signature);
    mSystemManager->EntitySignatureChanged(entity, signature);
  }

private:
  std::unique_ptr<ComponentManager> mComponentManger;
  std::unique_ptr<SystemManager> mSystemManager;
  std::unique_ptr<EntityManager> mEntityManager;
};

} // namespace engine::ecs
