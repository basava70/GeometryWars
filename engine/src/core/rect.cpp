#include "engine/rect.hpp"
#include <SDL3/SDL_rect.h>

namespace engine {
SDL_FRect RectF::toSDL() const { return {x - w / 2.0f, y - h / 2.0f, w, h}; }

} // namespace engine
