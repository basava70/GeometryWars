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

bool Game::init() {

  bool windowSuccess = mWindow.init("Geometry Wars", GameConfig::cLogicalWidth,
                                    GameConfig::cLogicalHeight);
  bool rendererSucess = mRenderer.init(mWindow, GameConfig::cLogicalWidth,
                                       GameConfig::cLogicalHeight);

  mInput.bindKey(SDLK_H, Action::WalkLeft);
  mInput.bindKey(SDLK_L, Action::WalkRight);
  mInput.bindKey(SDLK_J, Action::WalkDown);
  mInput.bindKey(SDLK_K, Action::WalkUp);

  mInput.bindAction(Action::WalkLeft, std::make_unique<WalkingLeftCommand>(
                                          GameConfig::cPlayerSpeed));
  mInput.bindAction(Action::WalkRight, std::make_unique<WalkingRightCommand>(
                                           GameConfig::cPlayerSpeed));
  mInput.bindAction(Action::WalkDown, std::make_unique<WalkingDownCommand>(
                                          GameConfig::cPlayerSpeed));
  mInput.bindAction(Action::WalkUp, std::make_unique<WalkingUpCommand>(
                                        GameConfig::cPlayerSpeed));

  mPlayer = mRegistry.create();
  auto walkingSheet = std::make_shared<engine::core::Texture>();
  auto runningSheet = std::make_shared<engine::core::Texture>();
  bool loadRunning = runningSheet->loadFromFile(mRenderer, "assets/Run.png");
  bool loadWalking = walkingSheet->loadFromFile(mRenderer, "assets/Walk.png");
  bool loadSuccess = loadRunning && loadWalking;

  mRegistry.emplace<Transform>(mPlayer, 500.f, 500.f, GameConfig::cPlayerSize,
                               GameConfig::cPlayerSize, 0.f);
  const int numberOfSprites = 8;
  const float spriteWidth = 1024.f / numberOfSprites;
  const float spriteHeight = 128.f;

  // regsiter walking
  mRegistry.emplace<Renderable>(
      mPlayer, walkingSheet, SDL_FRect{0.0f, 0.0f, spriteWidth, spriteHeight});
  mRegistry.emplace<Velocity>(mPlayer, 0, 0);

  return windowSuccess && rendererSucess && loadSuccess;
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
