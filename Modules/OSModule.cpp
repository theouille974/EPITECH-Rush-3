#include "OSModule.hpp"
#include <sys/utsname.h>

namespace Krell {
    OSModule::OSModule() {
        _name = "OS Module";
        update();
    }

    OSModule::~OSModule() {}

    void OSModule::update() {
        struct utsname buffer;
        if (uname(&buffer) != -1) {
            _data = "System: " + std::string(buffer.sysname) + "\n";
            _data += "Node: " + std::string(buffer.nodename) + "\n";
            _data += "Release: " + std::string(buffer.release) + "\n";
            _data += "Version: " + std::string(buffer.version) + "\n";
            _data += "Machine: " + std::string(buffer.machine);
        }
    }
}