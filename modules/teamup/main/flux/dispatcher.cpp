#include "flux/dispatcher.h"
#include <easylogging++.h>
#include <map>

namespace Teamup {
    namespace Flux {
        /** The map of action handlers */
        static std::multimap<std::string, std::function<void(const Action&)>> handlers;

        void dispatch(const Action& action) {
            auto range = handlers.equal_range(action.name());
            for (auto it = range.first; it != range.second; ++it) {
                it->second(action);
            }
        }
        void listen(const std::string& actionName, std::function<void(const Action&)> handler) {
            LOG(DEBUG) << "Registered new listener for: " << actionName;
            std::pair<std::string, std::function<void(const Action&)> > newPair(actionName, handler);
            handlers.insert(newPair);
        }
    }
}
