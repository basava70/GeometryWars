#pragma once

#include "engine/Input.hpp"
#include "engine/Renderer.hpp"
#include "engine/Window.hpp"
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
