#pragma once

#include "engine/ecs/Entity.hpp"
#include <memory.h>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace engine::ecs {

class IComponentArray {

  virtual ~IComponentArray() = default;

  virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T> class ComponentArray : public IComponentArray {
public:
  void insert(Entity entity, T const &component);

  void remove(Entity entity);

  T &get(Entity entity);

  void entityDestroyed(Entity entity) override;

private:
  std::unordered_map<Entity, T> mComponentMap;
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
