#pragma once

#include "engine/ecs/EntityManager.hpp"
#include "engine/ecs/EntitySet.hpp"
#include <cassert>
#include <memory>
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
    mSystems.resize(MAX_SYSTEMS);
    mSignatures.resize(MAX_SYSTEMS);
  }

  template <typename T> void registerSystem() {
    SystemType type = getSystemType<T>();

    assert(type < MAX_SYSTEMS &&
           "MAX_SYSTEMS reached, cannot register more systems");

    assert(!mSystems[type] && "Registering system more than once");
    mSystems[type] = std::make_shared<T>();
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

  void entityDestroyed(Entity entity) {
    for (auto &system : mSystems) {
      if (system)
        system->mEntitySet.remove(entity);
    }
  }

  void entitySignatureChanged(Entity entity, Signature const &entitySignature) {
    for (SystemType type = 0; type < mNextSystemType; type++) {
      auto &system = mSystems[type];
      if (!system)
        continue;
      Signature const &systemSignature = mSignatures[type];
      if ((entitySignature & systemSignature) == systemSignature)
        mSystems[type]->mEntitySet.insert(entity);
      else
        mSystems[type]->mEntitySet.remove(entity);
    }
  }

private:
  std::vector<std::shared_ptr<ISystem>> mSystems;
  inline static SystemType mNextSystemType{0};
  std::vector<Signature> mSignatures;

  template <typename T> SystemType getSystemType() {
    static SystemType type = mNextSystemType++;
    return type;
  }
};

} // namespace engine::ecs
