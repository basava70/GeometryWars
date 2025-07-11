#include "engine/input.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <memory>

namespace engine {

void Input::init() {
  mCurrentKeys.clear();
  mJustPressed.clear();
  mJustReleased.clear();
}

void Input::update() {
  mJustPressed.clear();
  mJustReleased.clear();
}

void Input::processEvent(SDL_Event const &e) {
  SDL_Keycode key = e.key.key;
  if (e.type == SDL_EVENT_KEY_DOWN) {
    if (!mCurrentKeys.contains(key)) {
      mJustPressed.insert(key);
      mCurrentKeys.insert(key);
      if (mKeyToAction.contains(key)) {
        dispatchAction(mKeyToAction[key]);
      }
    }
  } else if (e.type == SDL_EVENT_KEY_UP) {
    if (mCurrentKeys.contains(key)) {
      mJustReleased.insert(key);
      mCurrentKeys.erase(key);
    }
  }
}

bool Input::isKeyPressed(SDL_Keycode key) { return mCurrentKeys.contains(key); }

bool Input::isKeyJustPressed(SDL_Keycode key) {
  return mJustPressed.contains(key);
}

bool Input::isKeyJustReleased(SDL_Keycode key) {
  return mJustReleased.contains(key);
}

void Input::bindKey(SDL_Keycode key, Action action) {
  mKeyToAction[key] = action;
}

void Input::bindAction(Action action, std::unique_ptr<Command> command) {
  mActionToCommand[action] = std::move(command);
}

void Input::dispatchAction(Action action) {
  if (mActionToCommand.contains(action)) {
    mCommandQueue.push(std::move(mActionToCommand[action]));
  }
}

bool Input::hasPendingCommand() { return !mCommandQueue.empty(); }

std::unique_ptr<Command> Input::popCommand() {
  auto cmd = std::move(mCommandQueue.front());
  mCommandQueue.pop();
  return cmd;
}

} // namespace engine
