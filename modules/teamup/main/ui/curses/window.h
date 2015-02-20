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
                 * Get the X-Ordinate
                 * @return The X-Ordinate
                 */
                unsigned int x() const;
                /**
                 * Get the Y-Ordinate
                 * @return The Y-Ordinate
                 */
                unsigned int y() const;
                /**
                 * Get the Width
                 * @return The Width
                 */
                unsigned int width() const;
                /**
                 * Get the Height
                 * @return the Height
                 */
                unsigned int height() const;
                /**
                 * Get the title
                 * @return the title
                 */
                const std::string& title() const;
                /**
                 * Get if we are drawing a border or not
                 * @return true if we will draw a border. False if not
                 */
                bool bordered() const;

                /**
                 * Set the title for the window
                 * @param value The new title
                 */
                void title(const std::string& value);
                /**
                 * Set if we should draw a border or not
                 * @param value Whether we should draw a border or not
                 */
                void bordered(bool value);

                /**
                 * Get if the window is the current focus or not
                 * @return true if the window is focused. False if not
                 */
                bool focused() const;
                /**
                 * Set if the window is the current focus or not
                 * @param value true if the window is focused
                 */
                void focused(bool value);
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
