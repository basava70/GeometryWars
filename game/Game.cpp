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
#include <vector>

using namespace engine::core;
using namespace engine::components;
using namespace engine::systems;

bool Game::init() {

  bool windowSuccess = mWindow.init("Geometry Wars", GameConfig::cLogicalWidth,
                                    GameConfig::cLogicalHeight);
  bool rendererSucess = mRenderer.init(mWindow, GameConfig::cLogicalWidth,
                                       GameConfig::cLogicalHeight);

  mInput.bindKey(SDLK_H, Action::MoveLeft);
  mInput.bindKey(SDLK_L, Action::MoveRight);
  mInput.bindKey(SDLK_J, Action::MoveDown);
  mInput.bindKey(SDLK_K, Action::MoveUp);

  mInput.bindAction(Action::MoveLeft, std::make_unique<MoveLeftCommand>(
                                          GameConfig::cPlayerSpeed));
  mInput.bindAction(Action::MoveRight, std::make_unique<MoveRightCommand>(
                                           GameConfig::cPlayerSpeed));
  mInput.bindAction(Action::MoveDown, std::make_unique<MoveDownCommand>(
                                          GameConfig::cPlayerSpeed));
  mInput.bindAction(Action::MoveUp,
                    std::make_unique<MoveUpCommand>(GameConfig::cPlayerSpeed));

  mPlayer = mRegistry.create();
  auto sheet = std::make_shared<engine::core::Texture>();
  bool loadSuccess = sheet->loadFromFile(mRenderer, "assets/Run.png");

  mRegistry.emplace<Transform>(mPlayer, 500.f, 500.f, GameConfig::cPlayerSize,
                               GameConfig::cPlayerSize, 0.f);
  const int numberOfSprites = 8;
  const float spriteWidth = 1024.f / numberOfSprites;
  const float spriteHeight = 128.f;
  mRegistry.emplace<Renderable>(
      mPlayer, sheet, SDL_FRect{0.0f, 0.0f, spriteWidth, spriteHeight});
  mRegistry.emplace<Velocity>(mPlayer, 0, 0);

  std::vector<SDL_FRect> frames;

  for (int i = 0; i < numberOfSprites; i++) {
    frames.push_back(
        SDL_FRect{i * spriteWidth, 0.0f, spriteWidth, spriteHeight});
  }
  mRegistry.emplace<Animation>(mPlayer, frames, 0.0f, 0.1f, 0.0f, true);

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
  animationSystem(mRegistry, dt);
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
