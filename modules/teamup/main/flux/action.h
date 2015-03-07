#ifndef TEAMUP_FLUX_ACTION_H
#define TEAMUP_FLUX_ACTION_H

#include <string>

namespace Teamup {
    namespace Flux {
        /**
         * Base class for all Flux actions
         */
        class Action {
        public:
            /**
             * Construct the action
             * @param name The name of the action
             */
            Action(const std::string& name);
            /**
             * Get the name of the action
             * @return the name of the action
             */
            const std::string& name() const {
                return name_;
            }
            /**
             * Dispatch the action
             */
            void dispatch() const;
        protected:
        private:
            /** The name of the action */
            const std::string name_;
        };
    }
}

#endif // TEAMUP_FLUX_ACTION_H
