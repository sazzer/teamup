#ifndef TEAMUP_LOG_LOGSTORE_H
#define TEAMUP_LOG_LOGSTORE_H

#include <vector>
#include <string>

namespace Teamup {
    namespace Log {
        /**
         * Flux Store for storing log messages
         */
        class LogStore {
        public:
            const unsigned int count() const {
                return messages.size();
            }
            const std::string& message(const unsigned int i) const {
                return messages[messages.size() - i - 1];
            }
            void add(const std::string message) {
                messages.push_back(message);
            }
        protected:
        private:
            std::vector<std::string> messages;
        };
    }
}

#endif // TEAMUP_LOG_LOGSTORE_H
