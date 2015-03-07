#ifndef TEAMUP_UI_WINDOWS_LOG_H
#define TEAMUP_UI_WINDOWS_LOG_H

#include "ui/window_renderer.h"
#include "flux/stores.h"

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
                void operator()(Teamup::UI::WindowRenderer& renderer) {
                    const std::string& logStore = Teamup::Flux::stores().getStore<std::string>("log");

                    renderer.renderString(0, 0, "Hello, World");
                }
            protected:
            private:
            };
        }
    }
}

#endif // TEAMUP_UI_WINDOWS_LOG_H
