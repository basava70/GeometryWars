#pragma once

#include "engine/core/Event.hpp"
#include <entt/entity/fwd.hpp>
#include <queue>
namespace engine::core {

class Command {
public:
  virtual void execute(entt::registry &registry, entt::entity e) = 0;
  virtual ~Command() = default;
};

class QuitCommand : public Command {
public:
  explicit QuitCommand(std::queue<Event> &q);
  void execute(entt::registry &registry, entt::entity e) override;
  ~QuitCommand();
};

class MoveCommand : public Command {
public:
  MoveCommand(float speed) : mSpeed(speed) {}

protected:
  float mSpeed;
};

class WalkingUpCommand : public MoveCommand {
public:
  WalkingUpCommand(float speed) : MoveCommand(speed) {}
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~WalkingUpCommand() override = default;
};
class WalkingDownCommand : public MoveCommand {
public:
  WalkingDownCommand(float speed) : MoveCommand(speed) {}
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~WalkingDownCommand() override = default;
};
class WalkingRightCommand : public MoveCommand {
public:
  WalkingRightCommand(float speed) : MoveCommand(speed) {}
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~WalkingRightCommand() override = default;
};
class WalkingLeftCommand : public MoveCommand {
public:
  WalkingLeftCommand(float speed) : MoveCommand(speed) {}
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~WalkingLeftCommand() override = default;
};

} // namespace engine::core
