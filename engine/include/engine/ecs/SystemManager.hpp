#pragma once

#include "engine/ecs/EntitySet.hpp"
namespace engine::ecs {

class System {

private:
  EntitySet<> mEntitySet;
};

class TransformSystem : public System {};

} // namespace engine::ecs
