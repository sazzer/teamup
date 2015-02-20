#include "entry.h"
#include <easylogging++.h>
#include <sys/stat.h>

INITIALIZE_EASYLOGGINGPP

/**
 * The list of places to find the logging configuration file
 */
static std::vector<std::string> LOGGING_CONFIG_FILES {
    "./logging.conf"
};

/**
 * Find the file to use to configure the logging system with
 * @return The name of the file to use. If this is the empty string then no file was found.
 */
std::string findLoggingFile() {
    std::string result;
    struct stat buffer;
    for (auto file : LOGGING_CONFIG_FILES) {
        if (stat(file.c_str(), &buffer) == 0) {
            result = file;
            break;
        }
    }
    return result;
}

/**
 * Configure the logging system from the standard logging file
 * @param filename The name of the file to use to configure the logging with
 */
void configureLoggingFromFile(const std::string& filename) {
    el::Configurations conf("./logging.conf");
    el::Loggers::reconfigureAllLoggers(conf);
}

/**
 * Configure the logging system correctly
 */
void configureLogging() {
    const std::string filename = findLoggingFile();
    if (filename.empty()) {
        // No file was found, so do the default configuration
    } else {
        // We found a file, so use that instead
        configureLoggingFromFile(filename);
    }
}

/**
 * The main function for the application
 * @param  argc The number of arguments
 * @param  argv The actual arguments
 * @return      The return code for the application
 */
int main(const int argc, const char** argv) {
    START_EASYLOGGINGPP(argc, argv);
    configureLogging();

    std::vector<std::string> params(argv, argv + argc);
    Teamup::entry(params);
    return 0;
}
