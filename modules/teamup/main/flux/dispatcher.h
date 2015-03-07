#ifndef TEAMUP_FLUX_DISPATCHER_H
#define TEAMUP_FLUX_DISPATCHER_H

#include <string>
#include <functional>
#include "flux/action.h"

namespace Teamup {
    namespace Flux {
        /**
         * Dispatch the given action
         * @param action The action to dispatch
         */
        void dispatch(const Action& action);

        /**
         * Allow a store to register that it wants to listen to certain actions
         * @param actionName the name of the action to listen to
         * @param handler the handler for the action
         */
        void listen(const std::string& actionName, std::function<void(const Action&)> handler);
    }
}

#endif // TEAMUP_FLUX_DISPATCHER_H
