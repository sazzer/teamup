#include "entry.h"
#include <iostream>
#include <easylogging++.h>

namespace Teamup {
    void entry(const std::vector<std::string>& params) {
        LOG(INFO) << "Starting...";
        LOG(INFO) << "Finishing...";
    }
}
