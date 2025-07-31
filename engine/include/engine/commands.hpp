#pragma once

#include "engine/event.hpp"
#include <cstdint>
#include <queue>
namespace engine {

using Entity = std::uint32_t;

class Command {
public:
  virtual void execute(Entity e) = 0;
  virtual ~Command() = default;
};

class QuitCommand : public Command {
public:
  explicit QuitCommand(std::queue<Event> &q);
  void execute(Entity e) override;
  ~QuitCommand();

private:
  std::queue<Event> &mEngineEventQueue;
};

} // namespace engine
