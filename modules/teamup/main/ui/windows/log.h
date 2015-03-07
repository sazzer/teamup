#ifndef TEAMUP_UI_WINDOWS_LOG_H
#define TEAMUP_UI_WINDOWS_LOG_H

#include "ui/window_renderer.h"

namespace Teamup {
    namespace UI {
        namespace Windows {
            /**
             * Handler for the Log Window
             */
            class LogWindow {
            public:
                /**
                 * Functor implementation to use for rendering the window
                 * @param renderer The renderer to write to
                 */
                void operator()(Teamup::UI::WindowRenderer& renderer);
            protected:
            private:
            };
        }
    }
}

#endif // TEAMUP_UI_WINDOWS_LOG_H
