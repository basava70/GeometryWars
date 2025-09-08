#include "Game.hpp"
#include "engine/core/Event.hpp"

bool Game::init() {
  bool windowSuccess = mWindow.init("Geometry Wars", 1000, 800);
  bool rendererSucess = mRenderer.init(mWindow.get());

  return windowSuccess || rendererSucess;
}

void Game::processInput() {
  mInput.processEvent();
  while (mInput.hasPendingEvents()) {
    switch (mInput.popEngineEvent()) {
    case engine::core::Event::Quit:
      mIsRunning = false;
      break;
    }
  }
}
void Game::update() { mRenderer.clear({211, 211, 255, 255}); }
void Game::render() { mRenderer.present(); }
void Game::shutdown() {}

void Game::run() {
  init();

  mIsRunning = true;
  while (mIsRunning) {
    processInput();
    update();
    render();
  }
}

Game::~Game() { shutdown(); }
