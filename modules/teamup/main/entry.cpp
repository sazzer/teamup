#include "entry.h"
#include <easylogging++.h>
#include "ui/ui.h"
#include "flux/stores.h"
#include "log/logstore.h"

namespace Teamup {
    void entry(const std::vector<std::string>& params) {
        LOG(INFO) << "Starting...";
        Teamup::Log::LogStore logStore;

        Teamup::Flux::stores().addStore("log", logStore);
        Teamup::UI::start();
        LOG(INFO) << "Finishing...";
    }
}
