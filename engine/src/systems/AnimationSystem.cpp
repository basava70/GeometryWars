#include "engine/components/Components.hpp"
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>

namespace engine::systems {
using namespace engine::components;

void animationSystem(entt::registry &registry, float dt) {
  auto view = registry.view<Renderable, Animation>();

  for (auto entity : view) {
    auto &renderable = view.get<Renderable>(entity);
    auto &animation = view.get<Animation>(entity);

    animation.timer += dt;

    while (animation.timer >= animation.frameDuration) {
      animation.currentFrame++;
      if (animation.currentFrame >= animation.frames.size()) {
        if (animation.loop) {
          animation.currentFrame = 0;
        } else {
          animation.currentFrame = animation.frames.size() - 1;
        }
      }
      renderable.mSrcRect = animation.frames[animation.currentFrame];
      animation.timer -= animation.frameDuration;
    }
  }
}
} // namespace engine::systems
