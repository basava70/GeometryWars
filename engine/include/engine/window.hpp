#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>

namespace engine {

template <typename T> struct WindowDeleter;

template <> struct WindowDeleter<SDL_Window> {
  void operator()(SDL_Window *window) {
    if (window)
      SDL_DestroyWindow(window);
  }
};

using SDLWindowPtr = std::unique_ptr<SDL_Window, WindowDeleter<SDL_Window>>;

class Window {
public:
  [[nodiscard]] bool init(std::string const &title, int width, int height,
                          SDL_WindowFlags);

  Window(Window const &) = delete;
  Window &operator=(Window const &) = delete;
  Window(Window &&) noexcept = delete;
  Window &operator=(Window &&) noexcept = delete;

  std::pair<int, int> getSize() const;

  std::string getTitle() const;

  SDL_Window *get() const;

  void shutdown() noexcept;

  ~Window();

private:
  SDLWindowPtr mWindow;
  int mHeight{0};
  int mWidth{0};
  std::string mTitle;
  SDL_WindowFlags mFlags{SDL_WINDOW_FULLSCREEN};
};

} // namespace engine
