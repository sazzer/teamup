#ifndef TEAMUP_UI_CURSES_WINDOWBOUNDS_H
#define TEAMUP_UI_CURSES_WINDOWBOUNDS_H

#include <easylogging++.h>

namespace Teamup {
    namespace UI {
        namespace Curses {
            /**
             * The bounds of the Window
             */
            struct WindowBounds {
                /** The X-Ordinate */
                unsigned int x;
                /** The Y-Ordinate */
                unsigned int y;
                /** The width */
                unsigned int width;
                /** The height */
                unsigned int height;
            };

            /**
             * Override operator<< to support EasyLoggint++
             * @param os The output stream to use
             * @param windowBounds The object to log
             * @return the output stream
             */
            el::base::type::ostream_t& operator<<(el::base::type::ostream_t& os, const WindowBounds& windowBounds);
        }
    }
}

#endif // TEAMUP_UI_CURSES_WINDOWBOUNDS_H
