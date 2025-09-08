#include "engine/core/Texture.hpp"
#include "engine/core/Rect.hpp"

namespace engine::core {

RectF Texture::getRect() const { return mRect; }

template <typename T> T *Texture::get() const { return mTexture.get(); }

} // namespace engine::core
