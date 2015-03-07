#include "log/logstore.h"
#include "log/logaction.h"
#include "flux/dispatcher.h"
#include <vector>

namespace Teamup {
    namespace Log {
        static std::vector<std::string> messages;

        unsigned int count() {
            return messages.size();
        }
        const std::string& message(const unsigned int i) {
            return messages[messages.size() - i - 1];
        }

        // TODO: Change this from static registration
        static bool registered = []() {
            Teamup::Flux::listen(Teamup::Log::LogAction::NAME, [](const auto& action) {
                const Teamup::Log::LogAction& logAction = (const Teamup::Log::LogAction&)action;
                messages.push_back(logAction.message());
            });
            return true;
        }();
    }
}
