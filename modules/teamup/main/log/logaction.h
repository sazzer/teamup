#ifndef TEAMUP_LOG_LOGACTION_H
#define TEAMUP_LOG_LOGACTION_H

#include "flux/action.h"
#include <string>

namespace Teamup {
    namespace Log {
        /**
         * Flux Action for creating a log message
         */
        class LogAction : public Teamup::Flux::Action {
        public:
            /** The name of the action */
            static const std::string NAME;
            /**
             * Construct the action
             * @param message The message to log
             */
            LogAction(const std::string& message) : Action(NAME), message_(message) {

            }
        protected:
        private:
            /** The message to log */
            std::string message_;
        };
    }
}

#endif // TEAMUP_LOG_LOGACTION_H
