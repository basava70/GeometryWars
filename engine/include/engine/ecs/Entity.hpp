#pragma once
#include <cstdint>
namespace engine::ecs {

using Entity = std::uint32_t;

class EntityManager {
public:
  Entity CreateEntity();
  void DestroyEntity();

private:
  Entity mNextEntityId{0};
};

} // namespace engine::ecs
