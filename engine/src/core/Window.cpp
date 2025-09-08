#include "engine/core/Window.hpp"
#include <print>

namespace engine::core {

bool Window::init(std::string const &title, int width, int height) {
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

SDL_Window *Window::get() const { return mWindow.get(); }

void Window::shutdown() noexcept { mWindow.reset(); }

Window::~Window() { shutdown(); }
} // namespace engine::core
