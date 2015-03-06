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
                /**
                 * Local implementation of the Window Renderer to use for rendering.
                 * Declaring a class here is a little weird, but it means that it can
                 * access the Impl object cleanly without anyone outside this file knowing.
                 */
                class WindowRendererImpl : public WindowRenderer {
                public:
                    /**
                     * Construct the renderer
                     * @param i The window implementation
                     */
                    WindowRendererImpl(Window::Impl& i) : impl(i) {}
                    /**
                     * Get the bounds of the window to render into
                     * @return the bounds
                     */
                    virtual WindowBounds bounds() const override {
                        return WindowBounds {
                            .x = impl.bounds.x + 1,
                            .y = impl.bounds.y + 1,
                            .width = impl.bounds.width - 2,
                            .height = impl.bounds.height - 2
                        };
                    }

                    /**
                     * Render a simple string at the given location
                     * @param x The X-Ordinate to render the string at
                     * @param y The Y-Ordinate to render the string at
                     * @param str The string to render
                     */
                    virtual void renderString(const unsigned int x, const unsigned int y, const std::string& str) override {
                        mvwprintw(impl.window, y + 1, x + 1, "%s", str.c_str());
                    }
                protected:
                    /** The window implementation */
                    Window::Impl& impl;
                };

                wclear(pImpl->window);
                wborder(pImpl->window, 0, 0, 0, 0, 0, 0, 0, 0);

                WindowRendererImpl renderer(*pImpl);
                pImpl->renderer(renderer);
                wnoutrefresh(pImpl->window);
            }
        }
    }
}
