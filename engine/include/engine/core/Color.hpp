

#include <SDL3/SDL_pixels.h>
#include <cstdint>
namespace engine::core {
struct Color {
  std::uint8_t r = 0;
  std::uint8_t g = 0;
  std::uint8_t b = 0;
  std::uint8_t a = 255;

  constexpr Color() noexcept = default;
  constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b,
                  std::uint8_t a)
      : r(r), g(g), b(b), a(a) {}
  inline SDL_Color toSDL() const { return {r, g, b, a}; }
};
} // namespace engine::core
