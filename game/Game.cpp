#include "Game.hpp"
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

  bool windowSuccess = mWindow.init("Geometry Wars", 1000, 800);
  bool rendererSucess = mRenderer.init(mWindow);

  mInput.bindKey(SDLK_H, Action::MoveLeft);
  mInput.bindKey(SDLK_L, Action::MoveRight);
  mInput.bindKey(SDLK_J, Action::MoveDown);
  mInput.bindKey(SDLK_K, Action::MoveUp);

  mInput.bindAction(Action::MoveLeft, std::make_unique<MoveLeftCommand>());
  mInput.bindAction(Action::MoveRight, std::make_unique<MoveRightCommand>());
  mInput.bindAction(Action::MoveDown, std::make_unique<MoveDownCommand>());
  mInput.bindAction(Action::MoveUp, std::make_unique<MoveUpCommand>());

  mPlayer = mRegistry.create();
  auto sheet = std::make_shared<engine::core::Texture>();
  bool loadSuccess = sheet->loadFromFile(mRenderer, "assets/vectorGlow.png");

  mRegistry.emplace<Transform>(mPlayer, 200.0f, 200.0f, mSpriteSize,
                               mSpriteSize, 0.0f);
  mRegistry.emplace<Velocity>(mPlayer, 0.f, 0.f);
  mRegistry.emplace<Renderable>(mPlayer, sheet,
                                SDL_FRect{0.f, 0.f, mSpriteSize, mSpriteSize});

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

    double const TARGET_FPS = 120.0;
    double const TARGET_FRAME_TIME = 1.0 / TARGET_FPS;

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
