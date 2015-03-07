#include "entry.h"
#include <easylogging++.h>
#include "ui/ui.h"
#include "log/logstore.h"
#include "log/logaction.h"

namespace Teamup {
    void entry(const std::vector<std::string>& params) {
        LOG(INFO) << "Starting...";
        Teamup::Log::LogAction("One").dispatch();
        Teamup::Log::LogAction("Two").dispatch();
        Teamup::Log::LogAction("Three").dispatch();
        Teamup::Log::LogAction("Four").dispatch();
        Teamup::Log::LogAction("Five").dispatch();

        Teamup::UI::start();
        LOG(INFO) << "Finishing...";
    }
}
