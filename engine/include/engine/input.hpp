#pragma once

#include "engine/action.hpp"
#include "engine/commands.hpp"
#include "engine/event.hpp"
#include <SDL3/SDL.h>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace engine {

class Input {
public:
  bool init();
  void update();
  void processEvent();

  bool isKeyPressed(SDL_Keycode);
  bool isKeyJustPressed(SDL_Keycode);
  bool isKeyJustReleased(SDL_Keycode);

  void bindKey(SDL_Keycode, Action);
  void bindAction(Action, std::unique_ptr<Command>);
  void dispatchAction(Action);

  bool hasPendingCommand();
  bool hasPendingEvents();
  Command *popCommand();
  Event popEngineEvent();

private:
  SDL_Event mEvent;

  std::unordered_set<SDL_Keycode> mCurrentKeys;
  std::unordered_set<SDL_Keycode> mJustPressed;
  std::unordered_set<SDL_Keycode> mJustReleased;

  std::unordered_map<SDL_Keycode, Action> mKeyToAction;
  std::unordered_map<Action, std::unique_ptr<Command>> mActionToCommand;
  std::queue<Command *> mCommandQueue;
  std::queue<Event> mEventQueue;
};
} // namespace engine
