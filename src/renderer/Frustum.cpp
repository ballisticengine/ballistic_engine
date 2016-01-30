#include "renderer/Frustum.hpp"

Frustum::Frustum() : left(0), right(0), bottom(0), top(0), near(0), far(0) {
}

Frustum::Frustum(
        scalar_t left,
        scalar_t right,
        scalar_t bottom,
        scalar_t top,
        scalar_t near,
        scalar_t far
        ) : left(left), right(right), bottom(bottom), top(top), near(near), far(far) {
}

scalar_t Frustum::getWidth() {
    return abs(left)+abs(right);
}

scalar_t Frustum::getHeight() {
    return abs(top)+abs(bottom);
}