#pragma once

#include <SDL3/SDL.h>
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

private:
  inline static std::unordered_set<SDL_Keycode> mCurrentKeys;
  inline static std::unordered_set<SDL_Keycode> mJustPressed;
  inline static std::unordered_set<SDL_Keycode> mJustReleased;
};
} // namespace engine
