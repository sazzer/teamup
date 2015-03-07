#include "flux/action.h"
#include "flux/dispatcher.h"

namespace Teamup {
    namespace Flux {
        Action::Action(const std::string& name) : name_(name) {

        }
        void Action::dispatch() const {
            Teamup::Flux::dispatch(*this);
        }

    }
}
