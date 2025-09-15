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

class MoveUpCommand : public Command {
public:
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~MoveUpCommand() override = default;
};
class MoveDownCommand : public Command {
public:
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~MoveDownCommand() override = default;
};
class MoveRightCommand : public Command {
public:
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~MoveRightCommand() override = default;
};
class MoveLeftCommand : public Command {
public:
  virtual void execute(entt::registry &registry, entt::entity e) override;
  ~MoveLeftCommand() override = default;
};

} // namespace engine::core
