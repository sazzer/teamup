#include "ui/curses/curses.h"
#include <easylogging++.h>
#include <ncurses.h>
#include <map>
#include "ui/curses/window.h"

namespace Teamup {
    namespace UI {
        namespace Curses {
            struct Curses::Impl {
                std::map<std::string, std::unique_ptr<Window> > windows;
            };

            Curses::Curses() : pImpl(new Impl) {
                LOG(TRACE) << "Starting Curses";
                initscr();
                keypad(stdscr, TRUE);
                nonl();
                cbreak();
                echo();
                curs_set(0);
                refresh();

                if (has_colors())
                {
                    start_color();

                    for (int i = 0; i < COLORS; ++i) {
                        init_pair(i, i, COLOR_BLACK);
                    }
                }
            }

            Curses::~Curses() {
                LOG(TRACE) << "Stopping Curses";
                getch();
                endwin();
            }

            unsigned int Curses::width() const {
                return COLS;
            }

            unsigned int Curses::height() const {
                return LINES;
            }

            void Curses::render() const {
                for (const auto& win : pImpl->windows) {
                    VLOG(1) << "Rendering window: " << win.first;
                    win.second->render();
                }
                doupdate();
            }

            void Curses::createWindow(const std::string& name, const WindowBounds& bounds) {
                if (pImpl->windows.find(name) == pImpl->windows.end()) {
                    pImpl->windows[name].reset(new Window(bounds));
                    LOG(DEBUG) << "Created new window: " << name;
                }
            }
        }
    }
}
