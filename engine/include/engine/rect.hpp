#include <SDL3/SDL_rect.h>
namespace engine {
/**
 * \brief Generic rectangle class with float precision
 *
 * Represents a rectangle defined at the center
 */
struct RectF {
  /**
   * \brief Converts RectF to SDL_FRect
   * \return SDL_FRect with position aligned to topleft
   *
   * Note: The engine handles the change from center of
   * rectangle to topleft model of SDL
   *
   */
  SDL_FRect toSDL() const;

  float x; ///< x-coordinate of the center of rectangle
  float y; ///< y-coordinate of the center of rectangle
  float w; ///< width of the rectangle
  float h; ///< height of the rectangle
};
} // namespace engine
