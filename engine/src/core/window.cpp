#include "engine/window.hpp"
#include <print>

bool engine::Window::init(std::string const &title, int width, int height) {
  SDL_Window *raw = SDL_CreateWindow(title.c_str(), width, height, mFlags);
  if (!raw) {
    std::println("Error creating window: {}", SDL_GetError());
    return false;
  }
  mWindow.reset(raw);
  mTitle = title;
  mWidth = width;
  mHeight = height;
  return true;
}

SDL_Window *engine::Window::get() const { return mWindow.get(); }

void engine::Window::shutdown() noexcept { mWindow.reset(); }

engine::Window::~Window() { shutdown(); }
