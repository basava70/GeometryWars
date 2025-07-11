#pragma once

#include <cstdint>
namespace engine {

using Entity = std::uint32_t;

class Command {
public:
  virtual void execute(Entity e) = 0;
  virtual ~Command() = default;
};

} // namespace engine
