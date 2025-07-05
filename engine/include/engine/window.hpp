#pragma once

#include <SDL3/SDL.h>
#include <string>
namespace engine {
/**
 * \brief Manages SDL window for the engine.
 *
 * Window class wraps the SDL_Window and handles its lifetime.
 */
class Window {
public:
  Window() = default;
  ~Window();

  /**
   * \brief Initialises the SDL_Window
   * \param title Window title
   * \param width Window width in pixels
   * \param height Window height in pixels
   * \return true if successfull, false on failure
   */
  [[nodiscard]] bool init(std::string const &title, int width, int height,
                          SDL_WindowFlags flags = 0);

  /// \brief Destroys the SDL_Window and frees memory
  void shutdown() noexcept;

  /// \brief Returns the SDL_Window pointer
  SDL_Window *getWindow() const noexcept { return mWindow; };

  /// \brief Returns the current window width
  int getWidth() const noexcept { return mWidth; };

  /// \brief Returns the current window height
  int getHeight() const noexcept { return mHeight; };

  /// \brief Returns the current window title
  std::string getTitle() const { return mTitle; };

private:
  SDL_Window *mWindow{nullptr};
  int mWidth{0};
  int mHeight{0};
  std::string mTitle;
  SDL_WindowFlags mFlags{SDL_WINDOW_FULLSCREEN};
};
} // namespace engine
