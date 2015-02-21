#include "ui/curses/curses.h"
#include <easylogging++.h>
#include <ncurses.h>
#include <list>

namespace Teamup {
    namespace UI {
        namespace Curses {
            struct Curses::Impl {
                /** The map of existing windows */
                std::list<std::pair<std::string, std::unique_ptr<Window> > > windows_;
            };

            Curses::Curses() : pImpl(new Impl) {
                LOG(DEBUG) << "Starting Curses UI";
                // Do all of the initial setup
                initscr();
                keypad(stdscr, TRUE);
                nonl();
                cbreak();
                echo();
                if (has_colors()) {
                    start_color();

                    init_pair(1, COLOR_RED,     COLOR_BLACK);
                    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
                    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
                    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
                    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
                    init_pair(6, COLOR_CYAN,    COLOR_BLACK);
                    init_pair(7, COLOR_WHITE,   COLOR_BLACK);
                }

                clear();
            }
            Curses::~Curses() {
                LOG(DEBUG) << "Stopping Curses UI";
                endwin();
            }
            unsigned int Curses::width() const {
                return COLS;
            }
            unsigned int Curses::height() const {
                return LINES;
            }
            void Curses::render() {
                for (auto& win : pImpl->windows_) {
                    LOG(DEBUG) << "Rendering window: " << win.first;
                    win.second->render();
                }
                doupdate();
            }
            Window& Curses::createWindow(const std::string& name, 
                    const unsigned int x,
                    const unsigned int y,
                    const unsigned int width,
                    const unsigned int height) {
                LOG(DEBUG) << "Created new window: " << name;
                auto window = new Window(x, y, width, height);
                pImpl->windows_.push_back(
                        std::pair<std::string, std::unique_ptr<Window>>(
                            name, 
                            std::unique_ptr<Window>(window)));
                return *window;
            }
        }
    }
}

