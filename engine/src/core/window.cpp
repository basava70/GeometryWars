#include "engine/window.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>
#include <print>

bool engine::Window::init(std::string const &title, int width, int height,
                          SDL_WindowFlags flags) {
  mWindow = SDL_CreateWindow(title.c_str(), width, height, mFlags | flags);
  if (!mWindow) {
    std::println("Error creating window: {}", SDL_GetError());
    return false;
  }
  mTitle = title;
  mWidth = width;
  mHeight = height;
  return true;
}

void engine::Window::shutdown() noexcept {
  if (mWindow)
    SDL_DestroyWindow(mWindow);
}

engine::Window::~Window() { shutdown(); }
