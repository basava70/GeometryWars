#include "engine/texture.hpp"
#include "engine/rect.hpp"

namespace engine {

RectF Texture::getRect() const { return mRect; }

template <typename T> T *Texture::get() const { return mTexture.get(); }

} // namespace engine
