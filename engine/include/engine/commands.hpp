#pragma once

#include <cstdint>
#include <functional>
namespace engine {

using Entity = std::uint32_t;

class Command {
public:
  virtual void execute(Entity e) = 0;
  virtual ~Command() = default;
};

class QuitCommand : public Command {
  explicit QuitCommand(std::function<void()> callable);
  void execute(Entity e) override;
  ~QuitCommand();

private:
  std::function<void()> mCallable;
};

} // namespace engine
