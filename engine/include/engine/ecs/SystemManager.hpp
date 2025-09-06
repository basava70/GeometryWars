#pragma once

#include "engine/ecs/EntitySet.hpp"
#include <array>
#include <cassert>
#include <memory>
#include <type_traits>
namespace engine::ecs {

constexpr std::size_t MAX_SYSTEMS = 64;
using SystemType = std::uint8_t;

class ISystem {
public:
  virtual void update(float dt) = 0;

private:
  EntitySet<> mEntitySet;
};

class TransformSystem : public ISystem {};

class SystemManager {

public:
  SystemManager() { mSystems.reserve(MAX_SYSTEMS); }
  template <typename T> std::shared_ptr<T> registerSystem() {
    static_assert(std::is_base_of_v<ISystem, T>, "T must inherit from ISystem");
    SystemType type = getSystemType<T>();

    assert(type < MAX_SYSTEMS &&
           "MAX_SYSTEMS reached, cannot register more systems");

    assert(!mSystems[type] && "Registering system more than once");
    mSystems[type] = std::make_shared<T>();
    return;
  }

  template <typename T> SystemType getSystemType() {
    static SystemType type = mNextSystemType++;
    return type;
  }

private:
  std::vector<std::shared_ptr<ISystem>> mSystems;
  SystemType mNextSystemType{0};
};

} // namespace engine::ecs
