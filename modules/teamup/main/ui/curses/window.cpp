#include "ui/curses/window.h"
#include <easylogging++.h>
#include <ncurses.h>

namespace Teamup {
    namespace UI {
        namespace Curses {
            struct Window::Impl {
                /** The X-Ordinate of the window */
                unsigned int x_;
                /** The Y-Ordinate of the window */
                unsigned int y_;
                /** The width of the window */
                unsigned int width_;
                /** The height of the window */
                unsigned int height_;
                /** The NCurses Window */
                WINDOW* window_;
            };
            Window::Window(unsigned int x, unsigned int y, unsigned int width, unsigned int height) : pImpl(new Impl) {
                pImpl->x_ = x;
                pImpl->y_ = y;
                pImpl->width_ = width;
                pImpl->height_ = height;
                pImpl->window_ = newwin(height, width, y, x);
            }
            Window::~Window() {
                delwin(pImpl->window_);
            }
            void Window::render() {
                box(pImpl->window_, 0, 0);
                wnoutrefresh(pImpl->window_);
            }
        }
    }
}