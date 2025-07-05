#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>

namespace engine {

class Renderer {
public:
  bool init(SDL_Window *);
  void clear();

private:
};
} // namespace engine
