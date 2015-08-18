#include "renderer/Frustum.hpp"

Frustum::Frustum() : left(0), right(0), bottom(0), top(0), near(0), far(0) {
}

Frustum::Frustum(
        e_loc left,
        e_loc right,
        e_loc bottom,
        e_loc top,
        e_loc near,
        e_loc far
        ) : left(left), right(right), bottom(bottom), top(top), near(near), far(far) {
}