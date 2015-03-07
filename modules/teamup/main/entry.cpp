#include "entry.h"
#include <easylogging++.h>
#include "ui/ui.h"
#include "flux/stores.h"

namespace Teamup {
    void entry(const std::vector<std::string>& params) {
        LOG(INFO) << "Starting...";
        Teamup::Flux::stores().addStore<std::string>("log", "log");
        Teamup::UI::start();
        LOG(INFO) << "Finishing...";
    }
}
