#include "HostModule.hpp"
#include <unistd.h>
#include <limits.h>

namespace Krell {
    HostModule::HostModule() {
        _name = "Host Module";
        update();
    }

    HostModule::~HostModule() {}

    void HostModule::update() {
        char hostname[HOST_NAME_MAX];
        if (gethostname(hostname, HOST_NAME_MAX) == 0) {
            _data = "Hostname: " + std::string(hostname);
        }
    }
}