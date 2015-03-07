#ifndef TEAMUP_FLUX_STORES_H
#define TEAMUP_FLUX_STORES_H

#include <string>
#include <boost/any.hpp>
#include <memory>

namespace Teamup {
    namespace Flux {
        class Stores {
        public:
            /**
             * Construct the stores object
             */
            Stores();
            /**
             * Get the store with the given name
             * @param neme The name of the store
             * @return the store
             */
            template <typename T>
            T& getStore(const std::string& name) const {
                return boost::any_cast<T&>(getAnyStore(name));
            }

            template <typename T>
            void addStore(const std::string& name, T store) {
                addAnyStore(name, store);
            }
        protected:
        private:
            /**
             * Get the store with the given name
             * @param neme The name of the store
             * @return the store
             */
            boost::any& getAnyStore(const std::string& name) const;
            /**
             * Add the store with the given name
             * @param name The name of the store
             * @param store The store
             */
            void addAnyStore(const std::string& name, boost::any store);

            /** The implementation struct */
            struct Impl;
            /** The pImpl */
            std::unique_ptr<Impl> pImpl;
        };

        /**
         * Get the global list of all stores
         * @return the list of stores
         */
        Stores& stores();
    }
}

#endif // TEAMUP_FLUX_STORES_H
