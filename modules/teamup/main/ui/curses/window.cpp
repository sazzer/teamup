#include "ui/curses/window.h"
#include <ncurses.h>

namespace Teamup {
    namespace UI {
        namespace Curses {
            struct Window::Impl {
                WINDOW* window;
                WindowBounds bounds;
                std::function<void(WindowRenderer&)> renderer;
            };

            /**
             * Local implementation of the Window Renderer to use for rendering.
             * Declaring a class here is a little weird, but it means that it can
             * access the Impl object cleanly without anyone outside this file knowing.
             */
            class WindowRendererImpl : public WindowRenderer {
            public:
                /**
                 * Construct the renderer
                 * @param bounds The window bounds of the actual window
                 * @param window The Curses Window pointer
                 */
                 WindowRendererImpl(const WindowBounds& bounds, WINDOW*& window) : bounds_ {
                     .x = bounds.x + 1,
                     .y = bounds.y + 1,
                     .width = bounds.width - 2,
                     .height = bounds.height - 2
                 }, window_(window) {}

                /**
                 * Get the bounds of the window to render into
                 * @return the bounds
                 */
                virtual const WindowBounds& bounds() const override {
                    return bounds_;
                }

                /**
                 * Render a simple string at the given location
                 * @param x The X-Ordinate to render the string at
                 * @param y The Y-Ordinate to render the string at
                 * @param str The string to render
                 */
                virtual void renderString(const unsigned int x, const unsigned int y, const std::string& str) override {
                    mvwprintw(window_, y + 1, x + 1, "%s", str.c_str());
                }
            protected:
                /** The bounds of the window */
                const WindowBounds bounds_;
                /** The actual window */
                WINDOW* window_;
            };

            Window::Window(const WindowBounds& bounds, std::function<void(WindowRenderer&)> renderer) : pImpl(new Impl) {
                pImpl->bounds = bounds;
                pImpl->renderer = renderer;
                pImpl->window = newwin(bounds.height,
                        bounds.width,
                        bounds.y,
                        bounds.x);
            }

            Window::~Window() {
                delwin(pImpl->window);
            }

            const WindowBounds& Window::bounds() const {
                return pImpl->bounds;
            }

            void Window::render() {
                wclear(pImpl->window);
                wborder(pImpl->window, 0, 0, 0, 0, 0, 0, 0, 0);

                WindowRendererImpl renderer(pImpl->bounds, pImpl->window);
                pImpl->renderer(renderer);
                wnoutrefresh(pImpl->window);
            }
        }
    }
}
