#include "engine/commands.hpp"
namespace engine {

QuitCommand::QuitCommand(std::function<void()> callable)
    : mCallable(std::move(callable)) {}

void QuitCommand::execute(Entity e) { mCallable(); }

} // namespace engine
