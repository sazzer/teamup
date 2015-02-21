#include "ui/curses/curses.h"
#include <easylogging++.h>
#include <ncurses.h>
#include <list>

namespace Teamup {
    namespace UI {
        namespace Curses {
            /** The map of existing windows */
            static std::list<std::pair<std::string, std::unique_ptr<Window> > > windows;
            /** The map of colour pairs */
            static std::map<std::pair<Colours, int>, int> colourPairs;

            /**
             * Create a new colour for the given colour and shade
             * @param colour The name of the colour
             * @param shade The shade of the colour
             * @param r The red component of the colour
             * @param g The green component of the colour
             * @param b The blue component of the colour
             */
            void createColour(Colours colour, int shade, short r, short g, short b) {
                std::string colourName;
                int colourOffset;
                switch (colour) {
                    case Colours::BLACK: 
                        colourName = "Black"; 
                        colourOffset = 0;
                        break;
                    case Colours::RED: 
                        colourName = "Red"; 
                        colourOffset = 1;
                        break;
                    case Colours::GREEN: 
                        colourName = "Green"; 
                        colourOffset = 2;
                        break;
                    case Colours::YELLOW: 
                        colourName = "Yellow"; 
                        colourOffset = 3;
                        break;
                    case Colours::BLUE: 
                        colourName = "Blue"; 
                        colourOffset = 4;
                        break;
                    case Colours::MAGENTA: 
                        colourName = "Magenta"; 
                        colourOffset = 5;
                        break;
                    case Colours::CYAN: 
                        colourName = "Cyan"; 
                        colourOffset = 6;
                        break;
                    case Colours::WHITE: 
                        colourName = "White"; 
                        colourOffset = 7;
                        break;
                }

                int colourId = (shade * 7) + colourOffset + 1; // 1 is for the Black index 1
                LOG(DEBUG) << colourName << "(" << shade << ") = (" << r << ", " << g << ", " << b << ")[" << colourId << "]";
                init_color(colourId, r, g, b);
                init_pair(colourId, colourId, 1);

                colourPairs[std::pair<Colours, int>(colour, shade)] = colourId;
            }
            int getColour(Colours colour, int shade) {
                return colourPairs[std::pair<Colours, int>(colour, shade)];
            }

            /**
             * Initialize the colours to use
             */
            void initializeColours() {
                if (has_colors()) {
                    start_color();

                    if (can_change_color()) {
                        LOG(DEBUG) << "Redefining colours to give better options";
                        LOG(DEBUG) << "Supported colour: " << COLORS;
                        LOG(DEBUG) << "Supported colour pairs: " << COLOR_PAIRS;

                        // We have 7 colours, and (COLORS - 1) allowed shades
                        // This is because there's no point having shades of black
                        unsigned int shades = (COLORS - 1) / 7; 
                        unsigned int shadeOffset = 1000 / shades; // Colour values are 0-1000 for some reason
                        LOG(DEBUG) << "Shades: " << shades;
                        LOG(DEBUG) << "Shade Offset: " << shadeOffset;

                        unsigned int shade = 1000 - (shades * shadeOffset);
                        init_color(1, 0, 0, 0);
                        for (int s = 0; s < shades; ++s) {
                            shade += shadeOffset;
                            createColour(Colours::RED, s, shade, 0, 0);
                            createColour(Colours::GREEN, s, 0, shade, 0);
                            createColour(Colours::BLUE, s, 0, 0, shade);
                            createColour(Colours::YELLOW, s, shade, shade, 0);
                            createColour(Colours::MAGENTA, s, shade, 0, shade);
                            createColour(Colours::CYAN, s, 0, shade, shade);
                            createColour(Colours::WHITE, s, shade, shade, shade);

                        }
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

                initializeColours();
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
                for (auto& win : windows) {
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
                windows.push_back(
                        std::pair<std::string, std::unique_ptr<Window>>(
                            name, 
                            std::unique_ptr<Window>(window)));
            }
            void configureWindow(const std::string& name, 
                    std::function<void(Window&)> callback) {
                for (auto& win : windows) {
                    if (win.first == name) {
                        callback(*(win.second));
                    }
                }
            }
            void focusWindow(const std::string& name) {
                for (auto& win : windows) {
                    win.second->focused(win.first == name);
                }
            }
        }
    }
}

