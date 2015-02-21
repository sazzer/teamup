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
                /** The title of the window */
                std::string title_;
                /** Whether the window is bordered or not */
                bool bordered_;
                /** Whether the window is focused or not */
                bool focused_;
                /** The NCurses Window */
                WINDOW* window_;
            };
            Window::Window(unsigned int x, unsigned int y, unsigned int width, unsigned int height) : pImpl(new Impl) {
                pImpl->x_ = x;
                pImpl->y_ = y;
                pImpl->width_ = width;
                pImpl->height_ = height;
                pImpl->title_ = "";
                pImpl->bordered_ = false;
                pImpl->focused_ = false;
                pImpl->window_ = newwin(height, width, y, x);
                LOG(DEBUG) << "Creating window";
            }
            Window::~Window() {
                delwin(pImpl->window_);
                LOG(DEBUG) << "Destroyed window";
            }
            unsigned int Window::x() const {
                return pImpl->x_;
            }
            unsigned int Window::y() const {
                return pImpl->y_;
            }
            unsigned int Window::width() const {
                return pImpl->width_;
            }
            unsigned int Window::height() const {
                return pImpl->height_;
            }
            const std::string& Window::title() const {
                return pImpl->title_;
            }
            bool Window::bordered() const {
                return pImpl->bordered_;
            }
            void Window::title(const std::string& value) {
                pImpl->title_ = value;
            }
            void Window::bordered(bool value) {
                pImpl->bordered_ = value;
            }

            bool Window::focused() const {
                return pImpl->focused_;
            }
            void Window::focused(bool value) {
                pImpl->focused_ = value;
            }
            void Window::render() {
                wattrset(pImpl->window_, 0);
                if (pImpl->bordered_) {
                    if (pImpl->focused_) {
                        wattron(pImpl->window_, A_BOLD);
                    }

                    box(pImpl->window_, 0, 0);
                    if (!pImpl->title_.empty()) {
                        std::string actualTitle = " " + pImpl->title_ + " ";
                        unsigned int titleWidth = actualTitle.length();
                        unsigned int titleOffset = (pImpl->width_ - titleWidth) / 2;

                        mvwprintw(pImpl->window_, 0, titleOffset, "%s", actualTitle.c_str());
                    }
                    wattroff(pImpl->window_, A_BOLD);
                }
                wnoutrefresh(pImpl->window_);
            }
        }
    }
}
