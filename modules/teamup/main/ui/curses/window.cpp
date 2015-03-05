#include "ui/curses/window.h"
#include <ncurses.h>

namespace Teamup {
    namespace UI {
        namespace Curses {
            struct Window::Impl {
                WINDOW* window;
                WindowBounds bounds;
                std::function<void(const WindowRenderer&)> renderer;
            };

            Window::Window(const WindowBounds& bounds, std::function<void(const WindowRenderer&)> renderer) : pImpl(new Impl) {
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

            void Window::render() const {
                wclear(pImpl->window);
                wborder(pImpl->window, 0, 0, 0, 0, 0, 0, 0, 0);

                WindowRenderer renderer;
                pImpl->renderer(renderer);
                wnoutrefresh(pImpl->window);
            }
        }
    }
}
