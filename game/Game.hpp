#pragma once

#include "engine/core/Input.hpp"
#include "engine/core/Renderer.hpp"
#include "engine/core/Window.hpp"
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>

class Game {
public:
  void run();
  ~Game();

private:
  bool mIsRunning = false;
  engine::core::Window mWindow;
  engine::core::Renderer mRenderer;
  engine::core::Input mInput;

  entt::registry mRegistry;
  entt::entity mPlayer;

  float const mSpriteSize = 256.0f;

  bool init();
  void processInput();
  void update(double dt);
  void render();
  void shutdown();
};
