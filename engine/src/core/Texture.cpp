#include "engine/Texture.hpp"
#include "engine/Rect.hpp"

namespace engine {

RectF Texture::getRect() const { return mRect; }

template <typename T> T *Texture::get() const { return mTexture.get(); }

} // namespace engine
