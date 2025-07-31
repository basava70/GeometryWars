#pragma once

#include "engine/input.hpp"
#include "engine/renderer.hpp"
#include "engine/window.hpp"
class Game {
public:
  void run();
  ~Game();

private:
  bool mIsRunning = false;
  engine::Window mWindow;
  engine::Renderer mRenderer;
  engine::Input mInput;

  bool init();
  void processInput();
  void update();
  void render();
  void shutdown();
};
