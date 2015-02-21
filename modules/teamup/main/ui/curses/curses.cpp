#include "ui/curses/curses.h"
#include <easylogging++.h>
#include <ncurses.h>
#include <list>

namespace Teamup {
    namespace UI {
        namespace Curses {
            /** The map of existing windows */
            static std::list<std::pair<std::string, std::unique_ptr<Window> > > windows_;

            /**
             * Initialize the colours to use
             */
            void initializeColours() {
                if (has_colors()) {
                    start_color();

                    if (can_change_color()) {
                        LOG(DEBUG) << "Redefining colours to give better options";
                        LOG(DEBUG) << "Supported colour pairs: " << COLOR_PAIRS;
                    } else {
                        LOG(DEBUG) << "Unable to redefine colours so using defaults";
                    }
                    init_pair(1, COLOR_RED,     COLOR_BLACK);
                    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
                    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
                    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
                    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
                    init_pair(6, COLOR_CYAN,    COLOR_BLACK);
                    init_pair(7, COLOR_WHITE,   COLOR_BLACK);
                }
            }

            void setup() {
                LOG(DEBUG) << "Starting Curses UI";
                // Do all of the initial setup
                initscr();
                keypad(stdscr, TRUE);
                nonl();
                cbreak();
                echo();

            }
            void shutdown() {
                LOG(DEBUG) << "Stopping Curses UI";
                endwin();
            }
            unsigned int width() {
                return COLS;
            }
            unsigned int height() {
                return LINES;
            }
            void render() {
                clear();
                for (auto& win : windows_) {
                    LOG(DEBUG) << "Rendering window: " << win.first;
                    win.second->render();
                }
                doupdate();
            }
            void createWindow(const std::string& name, 
                    const unsigned int x,
                    const unsigned int y,
                    const unsigned int width,
                    const unsigned int height) {
                LOG(DEBUG) << "Created new window: " << name;
                auto window = new Window(x, y, width, height);
                windows_.push_back(
                        std::pair<std::string, std::unique_ptr<Window>>(
                            name, 
                            std::unique_ptr<Window>(window)));
            }
            void configureWindow(const std::string& name, 
                    std::function<void(Window&)> callback) {
                for (auto& win : windows_) {
                    if (win.first == name) {
                        callback(*(win.second));
                    }
                }
            }
            void focusWindow(const std::string& name) {
                for (auto& win : windows_) {
                    win.second->focused(win.first == name);
                }
            }
        }
    }
}

