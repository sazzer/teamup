#include <memory>
#include "ui/curses/window.h"

namespace Teamup {
    namespace UI {
        namespace Curses {
            /**
             * Wrapper around the Curses interface
             */
            class Curses {
                public:
                    /**
                     * Create the curses wrapper
                     */
                    Curses();
                    /**
                     * Shut down the curses wrapper
                     */
                    ~Curses();
                    /**
                     * Get the width of the Curses UI
                     * @return the width
                     */
                    unsigned int width() const;
                    /**
                     * Get the height of the Curses UI
                     * @return the height
                     */
                    unsigned int height() const;
                    /**
                     * Render the UI
                     */
                    void render();
                    /**
                     * Create a new window to render into
                     * @param name The internal name of the window
                     * @param x The X-Ordinate
                     * @param y The Y-Ordinate
                     * @param width The width
                     * @param height The height
                     * @return a reference to the window
                     */
                    Window& createWindow(const std::string& name, 
                            const unsigned int x,
                            const unsigned int y,
                            const unsigned int width,
                            const unsigned int height);
                private:
                    /** The private implementation */
                    struct Impl;
                    /** The pImpl */
                    std::unique_ptr<Impl> pImpl;
            };
        }
    }
}
