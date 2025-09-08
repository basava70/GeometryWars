#pragma once

#include "engine/ecs/EntityManager.hpp"
#include "engine/ecs/SparseSet.hpp"
#include <array>
#include <cassert>
#include <memory>

namespace engine::ecs {

class IComponentArray {
public:
  virtual ~IComponentArray() = default;

  virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T> class ComponentArray : public IComponentArray {
public:
  ComponentArray() : mCurrEntitySize(0) {}

  void entityDestroyed(Entity entity) override {
    removeComponentDataImpl(entity);
  }

  void removeComponentDataImpl(Entity entity) { mSparseSet.remove(entity); }
  void addComponentDataImpl(Entity entity, T const &dataPoint) {
    mSparseSet.insert(entity, dataPoint);
  }

  T &getComponentDataImpl(Entity entity) { return mSparseSet.getData(entity); }

private:
  static constexpr std::size_t INVALID_INDEX = MAX_ENTITIES;
  std::size_t mCurrEntitySize;
  SparseSet<T> mSparseSet;
};

class ComponentManager {
public:
  template <typename T> void registerComponent() {

    ComponentType type = getComponentType<T>();

    assert(type < MAX_COMPONENTS &&
           "MAX_COMPONENTS reached, cannot register more components");

    assert(!mComponentArrays[type] && "Registering component more than once");
    mComponentArrays[type] = std::make_shared<ComponentArray<T>>();
  }

  template <typename T> ComponentType getComponentType() {
    static ComponentType type = mNextComponentType++;
    return type;
  }

  template <typename T>
  void addComponentData(Entity entity, T const &component) {
    GetComponentArray<T>()->addComponentDataImpl(entity, component);
  }

  template <typename T> void removeComponentData(Entity entity) {
    GetComponentArray<T>()->removeComponentDataImpl(entity);
  }

  template <typename T> T &getComponentData(Entity entity) {
    return GetComponentArray<T>()->getComponentDataImpl(entity);
  }

  void entityDestroyed(Entity entity) {
    for (auto const &componentArray : mComponentArrays) {
      componentArray->entityDestroyed(entity);
    }
  }

private:
  std::array<std::shared_ptr<IComponentArray>, MAX_COMPONENTS> mComponentArrays;

  ComponentType mNextComponentType{};

  template <typename T> std::shared_ptr<ComponentArray<T>> GetComponentArray() {
    ComponentType type = getComponentType<T>();
    auto ptr =
        std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[type]);
    assert(ptr && "Component not registered");
    return ptr;
  }
};

} // namespace engine::ecs
