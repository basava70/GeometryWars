#include "engine/rect.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <memory>

namespace engine {

/**
 * \brief Custom deleter for unique_ptr.
 *
 * Will be useful if we move out of SDL_Texture in the future.
 */
template <typename T> struct TextureDeleter;

/// Specitalization for SDL
template <> struct TextureDeleter<SDL_Texture> {
  void operator()(SDL_Texture *texture) {
    if (texture)
      SDL_DestroyTexture(texture);
  }
};
/// creating alias
template <typename T> using TexturePtr = std::unique_ptr<T, TextureDeleter<T>>;

/**
 * \brief Base Texture that abstracts the underlying
 * for our engine.
 * \param mTexture unique_ptr for the underlying texture pointer
 * \param mRect engine Rectangle that holds the size shape and position of
 * the texture
 */
struct Texture {

  /// \brief Constructs Texture from an image specified by path
  Texture(std::string const &path);

  /// \brief Constructs the Texture from a surface(specific fot SDL)
  Texture(SDL_Surface *);

  /**
   * \brief getter function for rectangle
   * \returns the const & of the Rectangle
   */
  RectF const &getRect() const;

  /**
   * \brief getter function
   * \returns Underlying Texture pointer
   */
  SDL_Texture *get() const;
  TexturePtr<SDL_Texture> mTexture;
  RectF mRect;
};
} // namespace engine
