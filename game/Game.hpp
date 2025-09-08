#pragma once

#include "engine/core/Input.hpp"
#include "engine/core/Renderer.hpp"
#include "engine/core/Window.hpp"
class Game {
public:
  void run();
  ~Game();

private:
  bool mIsRunning = false;
  engine::core::Window mWindow;
  engine::core::Renderer mRenderer;
  engine::core::Input mInput;

  bool init();
  void processInput();
  void update();
  void render();
  void shutdown();
};
