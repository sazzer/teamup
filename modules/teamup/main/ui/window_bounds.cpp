#include "ui/window_bounds.h"
#include <easylogging++.h>

namespace Teamup {
    namespace UI {
        el::base::type::ostream_t& operator<<(el::base::type::ostream_t& os, const WindowBounds& windowBounds) {
            os << "(" << windowBounds.x << ", " << windowBounds.y << ")-("
                << (windowBounds.x + windowBounds.width - 1) << ", " << (windowBounds.y + windowBounds.height - 1) << ") ["
                << windowBounds.width << " x " << windowBounds.height << "]";
            return os;
        }
    }
}
