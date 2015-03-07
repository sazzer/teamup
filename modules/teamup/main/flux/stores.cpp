#include "flux/stores.h"
#include <map>
#include <easylogging++.h>

namespace Teamup {
    namespace Flux {
        /** The actual stores object */
        std::unique_ptr<Stores> stores_;

        struct Stores::Impl {
            /** The actual map of stores */
            std::map<std::string, boost::any> stores;
        };

        Stores::Stores() : pImpl(new Impl) {

        }
        boost::any& Stores::getAnyStore(const std::string& name) const {
            LOG(DEBUG) << "Looking up store: " << name;
            if (pImpl->stores.find(name) == pImpl->stores.end()) {
                LOG(ERROR) << "Requested store doesn't exist: " << name;
                throw 1; // TODO: Fix
            }
            return pImpl->stores[name];
        }

        void Stores::addAnyStore(const std::string& name, boost::any store) {
            LOG(DEBUG) << "Adding store: " << name;
            if (pImpl->stores.find(name) != pImpl->stores.end()) {
                LOG(ERROR) << "Requested store already exists: " << name;
                throw 1; // TODO: Fix
            }
            pImpl->stores[name] = store;
        }
        Stores& stores() {
            if (!stores_) {
                stores_.reset(new Stores);
            }
            return *stores_;
        }

    }
}
