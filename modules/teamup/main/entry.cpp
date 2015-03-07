#include "entry.h"
#include <easylogging++.h>
#include "ui/ui.h"
#include "flux/stores.h"
#include "log/logstore.h"

namespace Teamup {
    void entry(const std::vector<std::string>& params) {
        LOG(INFO) << "Starting...";
        Teamup::Log::LogStore logStore;
        logStore.add("This is the first log message");
        logStore.add("This is the second log message");
        logStore.add("This is the third log message");
        logStore.add("This is the fourth log message");
        logStore.add("This is the fifth log message");

        Teamup::Flux::stores().addStore("log", logStore);
        Teamup::UI::start();
        LOG(INFO) << "Finishing...";
    }
}
