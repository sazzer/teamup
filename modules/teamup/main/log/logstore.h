#ifndef TEAMUP_LOG_LOGSTORE_H
#define TEAMUP_LOG_LOGSTORE_H

#include <string>

namespace Teamup {
    namespace Log {
        /**
         * Get the count of messages in the store
         * @return the count of messages
         */
        unsigned int count();
        /**
         * Get a specific message from the store
         * @param i The index of the message
         * @return the message
         */
        const std::string& message(const unsigned int i);

        /**
         * Register the store with the dispatcher
         */
        void registerStore();
    }
}

#endif // TEAMUP_LOG_LOGSTORE_H
