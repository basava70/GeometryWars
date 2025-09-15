#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>

namespace engine::core {

struct WindowDeleter {
  void operator()(SDL_Window *window) {
    if (window)
      SDL_DestroyWindow(window);
  }
};

using WindowPtr = std::unique_ptr<SDL_Window, WindowDeleter>;

class Window {
public:
  [[nodiscard]] bool init(std::string const &title, int width, int height);

  std::pair<int, int> getSize() const;

  std::string getTitle() const;

  SDL_Window *get() const;

  void shutdown() noexcept;

  int getHeight() { return mHeight; }
  int getWidth() { return mWidth; }

  ~Window();

private:
  WindowPtr mWindow;
  int mHeight{0};
  int mWidth{0};
  std::string mTitle;
  SDL_WindowFlags mFlags{};
};

} // namespace engine::core
