#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> map {
".........................####.+.....+...........................................",
"....................+.+.####....+.+...+.....################################....",
"........................####..+....+..+...####################################..",
"..................+..+..##Z#.+...+...+..########################################",
"........................##Z#..++......#####.............................########",
"....................+.+..##Z#..+....#####...+.............................######",
".........................#ZZ#.+...#Z###...+..................................###",
".....................+.+.#Z##...##Z#............................................",
".........................##Z#..##Z#...+..+......................................",
".....................++...#ZZ##Z##..+...........................................",
".......................+...#Z#Z##...+..+........................................",
"........................+...#4##..+.............................................",
".............~~~~....+....+.##Z#................................................",
"..........~~~~~~~~~~...+.+..###Z..+.............................................",
"........~~~~~~~~~~~~~~....Z+.#Z##.Z.............................................",
"......~~~~~~~~~~~~~~~~~~~....##1#..+.~~~..~~~...................................",
".....~~~~~~~~....~~~~~~~~~~~~##2#~~~~~~~~~~~~~~~~.....~~~.......................",
"....~~~~~~..........~~~~~~~~~#3##~~~~~~~~~~~~~~~~~~~~~~~~~~~....................",
"..~~~~~~..............~~~~~~~####~~~~~~~..~~~~~~~~~~~~~~~~~~~~~.................",
"~~~~~~...................~~~~####~~~~........~~~~~~~~~~~~~~~~~~~~~~.............",
"~~~~~.....................+..#Z##................~~~~...~~~~~~~~~~~~~~~.........",
"~~~~.........................####.+........................~~~~~~~~~~~~~~~~~....",
"~~.........................+.##Z#...+.........................~~~~~~~~~~~~~~~~~~",
"........................+.+...##Z#.....+..........................~~~~~~~~~~~~~~",
"..............................####...+................................~~~~~~~~~~",
".........................+.+...ZZ##...+....................................~~~~~",
"...............................##Z#............................................~",
"............................+...##Z#..+.+.......................................",
".................................Z###...........................................",
"..............................+...Z#Z#.+........................................"
};

int main(void) {
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

    unsigned int mapWidth = COLS;
    unsigned int mapHeight = LINES;
    unsigned firstRow = (mapHeight - map.size()) / 2;
    unsigned firstCol = (mapWidth - map[0].size()) / 2;

    unsigned int logSize = mapHeight - map.size() - 4;
    unsigned int statusStart = (firstCol - 1) + (map[0].size() + 2);
    unsigned int statusSize = COLS - statusStart;

    WINDOW* mapWindow = newwin(map.size() + 2, map[0].size() + 2, 0, firstCol - 1);
    WINDOW* logWindow = newwin(logSize + 2, mapWidth, map.size() + 2, 0);
    WINDOW* statusWindow = newwin(map.size() + 2, statusSize, 0, statusStart);
    WINDOW* questWindow = newwin(map.size() + 2, firstCol - 1, 0, 0);

    clear();
    wborder(mapWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(logWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(statusWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(questWindow, 0, 0, 0, 0, 0, 0, 0, 0);

    for (unsigned int r = 0; r < map.size(); ++r) {
        for (unsigned int c = 0; c < map[r].size(); ++c) {
            char s = map[r][c];
            wattrset(mapWindow, 0);
            switch (s) {
                case '~':
                    wattron(mapWindow, COLOR_PAIR(4));
                    break;
                case '.':
                    wattron(mapWindow, COLOR_PAIR(2));
                    break;
                case '+':
                    wattron(mapWindow, A_BOLD);
                    wattron(mapWindow, COLOR_PAIR(2));
                    break;
                case '#':
                    wattron(mapWindow, COLOR_PAIR(238));
                    break;
                case '1':
                case '2':
                case '3':
                case '4':
                    wattron(mapWindow, COLOR_PAIR(7));
                    wattron(mapWindow, A_REVERSE);
                    break;
                case 'Z':
                    wattron(mapWindow, COLOR_PAIR(249));
                    break;
            };
            mvwprintw(mapWindow, 1 + r, 1 + c, "%c", s);
        }
    }

    for (unsigned int i = 0; i < logSize; ++i) {
        mvwprintw(logWindow, i + 1, 1, "This is log message number %d to show how the logs will look", i);
    }

    mvwprintw(statusWindow, 1, 1, "1. Soveliss");
    mvwprintw(statusWindow, 2, 1, "H: 91/100");
    wattron(statusWindow, COLOR_PAIR(2));
    for (int i = 0; i < (statusSize - 13) * 0.91; ++i) {
        mvwprintw(statusWindow, 2, 12 + i, "%c", '#');
    }
    wattrset(statusWindow, 0);
    mvwprintw(statusWindow, 3, 1, "M: 0/0");

    mvwprintw(statusWindow, 5, 1, "2. Mialee");
    mvwprintw(statusWindow, 6, 1, "H: 100/100");
    wattron(statusWindow, COLOR_PAIR(2));
    for (int i = 0; i < (statusSize - 13); ++i) {
        mvwprintw(statusWindow, 6, 12 + i, "%c", '#');
    }
    wattrset(statusWindow, 0);
    mvwprintw(statusWindow, 7, 1, "M: 25/100");
    wattron(statusWindow, COLOR_PAIR(57));
    for (int i = 0; i < (statusSize - 13) * 0.25; ++i) {
        mvwprintw(statusWindow, 7, 12 + i, "%c", '#');
    }
    wattrset(statusWindow, 0);

    mvwprintw(statusWindow, 9, 1, "3. Eberk");
    mvwprintw(statusWindow, 10, 1, "H: 22/100");
    wattron(statusWindow, COLOR_PAIR(28));
    for (int i = 0; i < (statusSize - 13) * 0.22; ++i) {
        mvwprintw(statusWindow, 10, 12 + i, "%c", '#');
    }
    wattrset(statusWindow, 0);
    mvwprintw(statusWindow, 11, 1, "M: 75/100");
    wattron(statusWindow, COLOR_PAIR(18));
    for (int i = 0; i < (statusSize - 13) * 0.75; ++i) {
        mvwprintw(statusWindow, 11, 12 + i, "%c", '#');
    }
    wattrset(statusWindow, 0);

    wattron(statusWindow, A_UNDERLINE);
    mvwprintw(statusWindow, 13, 1, "4. Krusk");
    wattrset(statusWindow, 0);
    mvwprintw(statusWindow, 14, 1, "H: 4/100");
    wattron(statusWindow, COLOR_PAIR(22));
    for (int i = 0; i < (statusSize - 13) * 0.04; ++i) {
        mvwprintw(statusWindow, 14, 12 + i, "%c", '#');
    }
    wattrset(statusWindow, 0);
    mvwprintw(statusWindow, 15, 1, "M: 0/0");

    mvwprintw(questWindow, 1, 1, std::string("Deliver message to Lord Kandel").substr(0, firstCol - 3).c_str());

    mvwprintw(questWindow, 2, 1, std::string("Investigate bank robbery in Hawksburg").substr(0, firstCol - 3).c_str());

    wattrset(questWindow, COLOR_PAIR(238));
    mvwprintw(questWindow, 5, 1, std::string("Rescue Princess Alice").substr(0, firstCol - 6).c_str());
    wattrset(questWindow, COLOR_PAIR(1));
    mvwprintw(questWindow, 5, firstCol - 4, "%c", 'x');
    wattrset(questWindow, 0);

    wattrset(questWindow, COLOR_PAIR(238));
    mvwprintw(questWindow, 6, 1, std::string("Find Lost Temple of Kurduggon").substr(0, firstCol - 6).c_str());
    wattrset(questWindow, COLOR_PAIR(2));
    mvwprintw(questWindow, 6, firstCol - 4, "%c", '/');
    wattrset(questWindow, 0);

    wnoutrefresh(mapWindow);
    wnoutrefresh(logWindow);
    wnoutrefresh(statusWindow);
    wnoutrefresh(questWindow);

    doupdate();

    wgetch(mapWindow);
    delwin(mapWindow);
    delwin(logWindow);
    delwin(statusWindow);
    delwin(questWindow);
    endwin();
}
