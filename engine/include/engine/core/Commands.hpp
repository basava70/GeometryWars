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

class MoveUpCommand : public MoveCommand {
public:
  MoveUpCommand(float speed) : MoveCommand(speed) {}
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~MoveUpCommand() override = default;
};
class MoveDownCommand : public MoveCommand {
public:
  MoveDownCommand(float speed) : MoveCommand(speed) {}
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~MoveDownCommand() override = default;
};
class MoveRightCommand : public MoveCommand {
public:
  MoveRightCommand(float speed) : MoveCommand(speed) {}
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~MoveRightCommand() override = default;
};
class MoveLeftCommand : public MoveCommand {
public:
  MoveLeftCommand(float speed) : MoveCommand(speed) {}
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~MoveLeftCommand() override = default;
};

} // namespace engine::core
