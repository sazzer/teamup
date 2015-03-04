#ifndef TEAMUP_UI_CURSES_CURSES_H
#define TEAMUP_UI_CURSES_CURSES_H

namespace Teamup {
    namespace UI {
        namespace Curses {
            /**
             * The actual Curses UI Implementation
             */
            class Curses {
            public:
                /**
                 * Construct the Curses wrapper
                 */
                Curses();
                /**
                 * Destroy the Curses wrapper
                 */
                ~Curses();
                /**
                 * Get the Width of the UI
                 * @return The width of the UI
                 */
                unsigned int width() const;
                /**
                 * Get the Height of the UI
                 * @return The height of the UI
                 */
                unsigned int height() const;
            protected:
            private:
            };
        }
    }
}


#endif // TEAMUP_UI_CURSES_CURSES_H