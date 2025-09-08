#pragma once

#include "engine/ecs/EntityManager.hpp"
#include "engine/ecs/EntitySet.hpp"
#include <cassert>
#include <memory>
#include <type_traits>
#include <vector>
namespace engine::ecs {

constexpr std::size_t MAX_SYSTEMS = 64;
using SystemType = std::uint8_t;

class ISystem {
public:
  virtual void update(float dt) = 0;

  EntitySet<> mEntitySet;
};

class TransformSystem : public ISystem {};

class SystemManager {

public:
  SystemManager() {
    mSystems.reserve(MAX_SYSTEMS);
    mSignatures.reserve(MAX_SYSTEMS);
  }

  template <typename T> void registerSystem() {
    SystemType type = getSystemType<T>();

    assert(type < MAX_SYSTEMS &&
           "MAX_SYSTEMS reached, cannot register more systems");

    assert(!mSystems[type] && "Registering system more than once");
    mSystems[type] = std::make_shared<T>();
  }

  template <typename T> SystemType getSystemType() {
    static_assert(std::is_base_of_v<ISystem, T>, "T must inherit from ISystem");
    static SystemType type = mNextSystemType++;
    return type;
  }

  template <typename T> std::shared_ptr<T> getSystem() {
    SystemType type = getSystemType<T>();
    auto ptr = std::static_pointer_cast<T>(mSystems[type]);
    assert(ptr && "System not registered");
    return ptr;
  }

  template <typename T> void SetSignature(Signature signature) {
    auto type = getSystemType<T>();
    mSignatures[type] = signature;
  }

  template <typename T> void EntityDestroyed(Entity entity) {
    for (auto &system : mSystems) {
      system->mEntitySet.remove(entity);
    }
  }

  template <typename T>
  void EntitySignatureChanged(Entity entity, Signature const &entitySignature) {
    auto type = getSystemType<T>();
    auto &system = mSystems[type];
    Signature const &systemSignature = mSignatures[type];
    if ((systemSignature & entitySignature) == systemSignature) {
      system->mEntitySet.add(entity);
    } else {
      system->mEntitySet.remove(entity);
    }
  }

private:
  std::vector<std::shared_ptr<ISystem>> mSystems;
  SystemType mNextSystemType{0};
  std::vector<Signature> mSignatures;
};

} // namespace engine::ecs
