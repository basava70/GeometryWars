#pragma once
#include <SDL3/SDL_rect.h>
namespace engine {
/**
 * \brief Generic rectangle class with float precision
 *
 * Represents a rectangle defined at the center
 */
struct RectF {
  float x = 0; ///< x-coordinate of the center of rectangle
  float y = 0; ///< y-coordinate of the center of rectangle
  float w = 0; ///< width of the rectangle
  float h = 0; ///< height of the rectangle

  constexpr RectF() noexcept = default;
  constexpr RectF(float x, float y, float w, float h) noexcept
      : x(x), y(y), w(w), h(h) {}
  /**
   * \brief Converts RectF to SDL_FRect
   * \return SDL_FRect with position aligned to topleft
   *
   * Note: The engine handles the change from center of
   * rectangle to topleft model of SDL
   *
   */
  inline SDL_FRect toSDL() const { return {x - w / 2.0f, y - h / 2.0f, w, h}; }
};
} // namespace engine
