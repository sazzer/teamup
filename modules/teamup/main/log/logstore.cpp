#include "log/logstore.h"
#include <vector>

namespace Teamup {
    namespace Log {
        static std::vector<std::string> messages {
            "Five",
            "Four",
            "Three",
            "Two",
            "One"
        };

        unsigned int count() {
            return messages.size();
        }
        const std::string& message(const unsigned int i) {
            return messages[messages.size() - i - 1];
        }
    }
}
