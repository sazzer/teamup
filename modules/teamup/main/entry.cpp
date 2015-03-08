#include "entry.h"
#include <easylogging++.h>
#include "ui/ui.h"
#include "log/logstore.h"
#include "log/logaction.h"

namespace Teamup {
    void entry(const std::vector<std::string>& params) {
        LOG(INFO) << "Starting...";
        Teamup::Log::registerStore();

        Teamup::Log::LogAction("1").dispatch();
        Teamup::Log::LogAction("2").dispatch();
        Teamup::Log::LogAction("3").dispatch();
        Teamup::Log::LogAction("4").dispatch();
        Teamup::Log::LogAction("5").dispatch();
        Teamup::Log::LogAction("6").dispatch();
        Teamup::Log::LogAction("7").dispatch();
        Teamup::Log::LogAction("8").dispatch();
        Teamup::Log::LogAction("9").dispatch();
        Teamup::Log::LogAction("10").dispatch();
        Teamup::Log::LogAction("11").dispatch();
        Teamup::Log::LogAction("12").dispatch();
        Teamup::Log::LogAction("13").dispatch();
        Teamup::Log::LogAction("14").dispatch();
        Teamup::Log::LogAction("15").dispatch();

        Teamup::UI::start();
        LOG(INFO) << "Finishing...";
    }
}
