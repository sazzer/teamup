#include "entry.h"
#include <easylogging++.h>
#include "ui/ui.h"

namespace Teamup {
    void entry(const std::vector<std::string>& params) {
        LOG(INFO) << "Starting...";
        Teamup::UI::start();
        LOG(INFO) << "Finishing...";
    }
}
