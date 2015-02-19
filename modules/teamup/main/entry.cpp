#include "entry.h"
#include <iostream>
#include <easylogging++.h>

namespace Teamup {
    void entry(const std::vector<std::string>& params) {
        LOG(INFO) << "Hello, World!";
        for (auto p : params) {
            LOG(INFO) << "Param: " << p;
        }
    }
}
