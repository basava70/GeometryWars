#include "engine/core/Input.hpp"
#include "engine/core/Action.hpp"
#include "engine/core/Commands.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <memory>
#include <queue>

namespace engine::core {

bool Input::init() {
  mCurrentKeys.clear();
  mJustPressed.clear();
  mJustReleased.clear();
  return true;
}

void Input::update() {
  mJustPressed.clear();
  mJustReleased.clear();
}

void Input::processEvent() {
  while (SDL_PollEvent(&mEvent)) {
    switch (mEvent.type) {
    case SDL_EVENT_QUIT:
      mEventQueue.push(Event::Quit);
      break;
    case SDL_EVENT_KEY_DOWN: {
      SDL_Keycode key = mEvent.key.key;
      if (!mCurrentKeys.contains(key)) {
        mJustPressed.insert(key);
        mCurrentKeys.insert(key);
        if (mKeyToAction.contains(key)) {
          dispatchAction(mKeyToAction[key]);
        }
      }
      break;
    }
    case SDL_EVENT_KEY_UP: {
      SDL_Keycode key = mEvent.key.key;
      if (mCurrentKeys.contains(key)) {
        mJustReleased.insert(key);
        mCurrentKeys.erase(key);
      }
      break;
    }
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
    mCommandQueue.push(mActionToCommand[action].get());
  }
}

bool Input::hasPendingCommands() { return !mCommandQueue.empty(); }
bool Input::hasPendingEvents() { return !mEventQueue.empty(); }

Command *Input::popCommand() {
  auto cmd = mCommandQueue.front();
  mCommandQueue.pop();
  return cmd;
}

Event Input::popEngineEvent() {
  auto event = mEventQueue.front();
  mEventQueue.pop();
  return event;
}

} // namespace engine::core
