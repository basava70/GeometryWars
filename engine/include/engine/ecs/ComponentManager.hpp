#pragma once

#include "engine/ecs/Entity.hpp"
#include <cassert>
#include <cstddef>
#include <limits>
#include <memory.h>
#include <memory>
#include <print>
#include <typeindex>
#include <unordered_map>

namespace engine::ecs {

class IComponentArray {
public:
  virtual ~IComponentArray() = default;

  virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T> class ComponentArray : public IComponentArray {
public:
  void initialize() {
    entityIdToDataIndex.fill(INVALID_INDEX);
    entityId.fill(INVALID_INDEX);
    currEntitiesNum = 4;
    data = {"a", "b", "c", "d"};
    for (int i = 0; i < currEntitiesNum; i++) {
      entityId[i] = i;
      entityIdToDataIndex[i] = i;
    }
  }

  void entityDestroyed(Entity entity) override { remove(entity); }

  void print() {
    std::println("data : {} ", data);
    std::println("entityId : {} ", entityId);
    std::println("entityIdToDataIndex : {} ", entityIdToDataIndex);
  }
  void remove(Entity id) {

    if (entityIdToDataIndex[id] == INVALID_INDEX)
      return;

    std::size_t removedIndex = entityIdToDataIndex[id];
    data[removedIndex] = data[currEntitiesNum - 1];
    Entity backEntity = entityId[currEntitiesNum - 1];
    entityId[removedIndex] = backEntity;
    entityIdToDataIndex[id] = INVALID_INDEX;
    entityIdToDataIndex[backEntity] = removedIndex;
    currEntitiesNum--;
    print();
  }
  void add(Entity id, T const &dataPoint) {
    assert(
        currEntitiesNum <
        MAX_ENTITIES); /// make sure total entities are less than MAX_ENTITIES
    assert(entityIdToDataIndex[id] ==
           INVALID_INDEX); // check if the entity is not added to the component
                           // already

    data[++currEntitiesNum - 1] = dataPoint;
    entityId[currEntitiesNum - 1] = id;
    entityIdToDataIndex[id] = currEntitiesNum - 1;
    print();
  }

private:
  static constexpr std::size_t INVALID_INDEX = MAX_ENTITIES;
  std::size_t currEntitiesNum;
  std::array<T, MAX_ENTITIES> data;
  std::array<Entity, MAX_ENTITIES> entityId;
  std::array<std::size_t, MAX_ENTITIES> entityIdToDataIndex;
};
class ComponentManager {

public:
  template <typename T> void registerComponent();

  template <typename T> void addComponent(Entity entity, T const &component);

  template <typename T> void removeComponent(Entity entity);

  template <typename T> T &getComponent(Entity entity);

  void entityDestroyed(Entity entity);

private:
  std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>>
      mComponentArrays;
};

} // namespace engine::ecs
