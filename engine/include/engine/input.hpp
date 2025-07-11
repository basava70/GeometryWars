#pragma once

#include "engine/action.hpp"
#include "engine/commands.hpp"
#include <SDL3/SDL.h>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace engine {
class Input {
public:
  static void init();
  static void update();
  static void processEvent(SDL_Event const &e);

  static bool isKeyPressed(SDL_Keycode);
  static bool isKeyJustPressed(SDL_Keycode);
  static bool isKeyJustReleased(SDL_Keycode);

  static void bindKey(SDL_Keycode, Action);
  static void bindAction(Action, std::unique_ptr<Command>);
  static void dispatchAction(Action);

  static bool hasPendingCommand();
  static Command *popCommand();

private:
  inline static std::unordered_set<SDL_Keycode> mCurrentKeys;
  inline static std::unordered_set<SDL_Keycode> mJustPressed;
  inline static std::unordered_set<SDL_Keycode> mJustReleased;

  inline static std::unordered_map<SDL_Keycode, Action> mKeyToAction;
  inline static std::unordered_map<Action, std::unique_ptr<Command>>
      mActionToCommand;
  inline static std::queue<Command *> mCommandQueue;
};
} // namespace engine
