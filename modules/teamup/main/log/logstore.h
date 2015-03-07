#ifndef TEAMUP_LOG_LOGSTORE_H
#define TEAMUP_LOG_LOGSTORE_H

namespace Teamup {
    namespace Log {
        /**
         * Flux Store for storing log messages
         */
        class LogStore {
        public:
            const unsigned int count() const {
                return 5;
            }
            const std::string& message(const unsigned int i) const {
                return "Hello, World";
            }
        protected:
        private:
        };
    }
}

#endif // TEAMUP_LOG_LOGSTORE_H
