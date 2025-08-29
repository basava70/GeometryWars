#pragma once

#include "engine/ecs/Entity.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <memory.h>
#include <memory>
#include <print>

namespace engine::ecs {

class IComponentArray {
public:
  virtual ~IComponentArray() = default;

  virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T> class ComponentArray : public IComponentArray {
public:
  ComponentArray() : currEntitiesNum(0) {
    entityIdToDataIndex.fill(INVALID_INDEX);
    entityId.fill(INVALID_INDEX);
  }

  void entityDestroyed(Entity entity) override {
    removeComponentDataImpl(entity);
  }

  void print() {
    std::println("data : {} ", data);
    std::println("entityId : {} ", entityId);
    std::println("entityIdToDataIndex : {} ", entityIdToDataIndex);
  }
  void removeComponentDataImpl(Entity entity) {

    assert(entityIdToDataIndex[entity] != INVALID_INDEX &&
           "Entity is not attached to the component");

    std::size_t removedIndex = entityIdToDataIndex[entity];
    std::size_t lastIndex = currEntitiesNum - 1;

    if (removedIndex != lastIndex) {
      data[removedIndex] = data[lastIndex];
      Entity backEntity = entityId[lastIndex];
      entityId[removedIndex] = backEntity;
      entityIdToDataIndex[backEntity] = removedIndex;
    }

    entityIdToDataIndex[entity] = INVALID_INDEX;
    currEntitiesNum--;
    // print();
  }
  void addComponentDataImpl(Entity entity, T const &dataPoint) {
    assert(currEntitiesNum < MAX_ENTITIES &&
           "Exceeding MAX_ENTITIES"); /// make sure total entities are less than
                                      /// MAX_ENTITIES
    assert(
        entityIdToDataIndex[entity] == INVALID_INDEX &&
        "Entity is already attached to the component"); // check if the entity
                                                        // is not added to the
                                                        // component already

    data[currEntitiesNum] = dataPoint;
    entityId[currEntitiesNum] = entity;
    entityIdToDataIndex[entity] = currEntitiesNum;
    ++currEntitiesNum;
    // print();
  }

  T &getComponentDataImpl(Entity entity) {
    assert(entityIdToDataIndex[entity] != INVALID_INDEX &&
           "Entity is not attached to the component");
    std::size_t index = entityIdToDataIndex[entity];
    return data[index];
  }

private:
  static constexpr std::size_t INVALID_INDEX = MAX_ENTITIES;
  std::size_t currEntitiesNum;
  std::array<T, MAX_ENTITIES> data;
  std::array<Entity, MAX_ENTITIES> entityId;
  std::array<std::size_t, MAX_ENTITIES> entityIdToDataIndex;
};

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 64;

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
