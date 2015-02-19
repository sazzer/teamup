#include <vector>
#include <string>

namespace Teamup {
    /**
     * The main entrypoint for the game. This is explicitly *not* called main so that we can build a library - for unit testing against - and an executable
     * that links against that library and has a main method
     * @param params The parameters to the executable
     */
    void entry(const std::vector<std::string>& params);
}
