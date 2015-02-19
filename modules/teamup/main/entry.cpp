#include "entry.h"
#include <iostream>
#include <easylogging++.h>

namespace Teamup {
    void entry(const std::vector<const std::string>& params) {
        LOG(INFO) << "Hello, World!";
        std::for_each(params.begin(), params.end(), [](auto p) {
            LOG(INFO) << "Param: " << p;
        });
    }
}