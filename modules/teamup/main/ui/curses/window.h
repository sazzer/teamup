#include <memory>

namespace Teamup {
    namespace UI {
        namespace Curses {
            /**
             * Representation of a Window in the Curses UI
             */
            class Window {
            public:
                /**
                 * Create a new window
                 * @param x The X-Ordinate
                 * @param y The Y-Ordinate
                 * @param width The width
                 * @param height The height
                 */
                Window(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
                /**
                 * Destroy the window
                 */
                ~Window();
                /**
                 * Render the window
                 */
                void render();
            private:
                /** The private implementation */
                struct Impl;
                /** The pImpl */
                std::unique_ptr<Impl> pImpl;
            };
        }
    }
}