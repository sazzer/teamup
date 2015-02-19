#include "entry.h"

/**
 * The main function for the application
 * @param  argc The number of arguments
 * @param  argv The actual arguments
 * @return      The return code for the application
 */
int main(const int argc, const char** argv) {
    std::vector<const std::string> params(argv, argv + argc);
    Teamup::entry(params);
    return 0;
}
