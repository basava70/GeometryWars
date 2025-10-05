#include "Game.hpp"
#include "GameConfig.hpp"
#include "engine/components/Components.hpp"
#include "engine/core/Action.hpp"
#include "engine/core/Commands.hpp"
#include "engine/core/Event.hpp"
#include "engine/core/Texture.hpp"
#include "engine/systems/systems.hpp"
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <memory>

using namespace engine::core;
using namespace engine::components;
using namespace engine::systems;

void Game::initKeyBindings() {
  mInput.bindKey(SDLK_H, Action::WalkLeft);
  mInput.bindKey(SDLK_L, Action::WalkRight);

  mInput.bindAction(Action::WalkLeft, std::make_unique<WalkingLeftCommand>(
                                          GameConfig::cPlayerSpeed));
  mInput.bindAction(Action::WalkRight, std::make_unique<WalkingRightCommand>(
                                           GameConfig::cPlayerSpeed));
}

bool Game::initPlayer() {
  mPlayer = mRegistry.create();
  auto playerSheet = std::make_shared<engine::core::Texture>();

  // bool loadPlayer = playerSheet->loadFromFile(mRenderer,
  // "assets/Player.png");
  bool loadPlayer = playerSheet->loadFromFile(mRenderer, "assets/Walk.png");

  bool loadSuccess = loadPlayer;

  mRegistry.emplace<Transform>(mPlayer, 0.f, 500.f, GameConfig::cPlayerSize,
                               GameConfig::cPlayerSize, 0.f);

  // const float playerSheetWidth = 2048.f;
  // const float playerSheetHeight = 512.f;
  const float playerSheetWidth = 1024.f / 8.f;
  const float playerSheetHeight = 128.f;

  // regsiter walking
  mRegistry.emplace<Renderable>(
      mPlayer, playerSheet,
      SDL_FRect{0.0f, 0.0f, playerSheetWidth, playerSheetHeight});
  mRegistry.emplace<Velocity>(mPlayer, 0, 0);

  return loadSuccess;
}

bool Game::init() {
  bool windowSuccess = mWindow.init("Geometry Wars", GameConfig::cLogicalWidth,
                                    GameConfig::cLogicalHeight);
  bool rendererSucess = mRenderer.init(mWindow, GameConfig::cLogicalWidth,
                                       GameConfig::cLogicalHeight);
  initKeyBindings();
  bool loadPlayer = initPlayer();

  return loadPlayer;
}

void Game::processInput() {
  mInput.processEvent();
  while (mInput.hasPendingEvents()) {
    switch (mInput.popEngineEvent()) {
    case Event::Quit:
      mIsRunning = false;
      break;
    }
  }

  while (mInput.hasPendingCommands()) {
    Command *cmd = mInput.popCommand();
    if (cmd) {
      cmd->execute(mRegistry, mPlayer);
    }
  }
}
void Game::update(double dt) {
  mRenderer.clear({0, 0, 0, 255});
  movementSystem(mRegistry, dt);
  renderSystem(mRegistry, mRenderer);
}

void Game::render() { mRenderer.present(); }
void Game::shutdown() {}

void Game::run() {
  if (init()) {

    double const TARGET_FRAME_TIME = 1.0 / GameConfig::cExpectedFrameRate;

    uint64_t lastCounter = SDL_GetPerformanceCounter();

    mIsRunning = true;

    while (mIsRunning) {
      uint64_t frameStart = SDL_GetPerformanceCounter();
      double dt = (frameStart - lastCounter) /
                  static_cast<double>(SDL_GetPerformanceFrequency());
      lastCounter = frameStart;
      processInput();
      update(dt);
      render();

      uint64_t frameEnd = SDL_GetPerformanceCounter();
      double elapsed = (frameEnd - frameStart) /
                       static_cast<double>(SDL_GetPerformanceFrequency());

      if (elapsed < TARGET_FRAME_TIME) {
        double delaySec = TARGET_FRAME_TIME - elapsed;
        SDL_Delay(static_cast<Uint32>(delaySec * 1000.0));
      }
    }
  }
}

Game::~Game() { shutdown(); }
