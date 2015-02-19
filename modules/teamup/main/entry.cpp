#include "entry.h"
#include <iostream>

namespace Teamup {
    void entry(const std::vector<const std::string>& params) {
        std::cout << "Hello, World!" << std::endl;
        std::for_each(params.begin(), params.end(), [](auto p) {
            std::cout << "Param: " << p << std::endl;
        });
    }
}