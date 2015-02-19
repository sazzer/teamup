#include "entry.h"
#include "ui/ui.h"
#include <iostream>
#include <easylogging++.h>

namespace Teamup {
    void entry(const std::vector<std::string>& params) {
        LOG(INFO) << "Starting...";
        UI::start();
        LOG(INFO) << "Finishing...";
    }
}
