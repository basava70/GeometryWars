

#include <SDL3/SDL_pixels.h>
#include <cstdint>
struct Color {
  std::uint8_t r = 0;
  std::uint8_t g = 0;
  std::uint8_t b = 0;
  std::uint8_t a = 255;

  constexpr Color() noexcept = default;
  constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b,
                  std::uint8_t a)
      : r(r), g(g), b(b), a(a) {}
  SDL_Color toSDL() const { return SDL_Color{r, g, b, a}; }
};
