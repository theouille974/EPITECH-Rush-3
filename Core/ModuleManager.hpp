#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "../Modules/IModule.hpp"
#include <deque>
#include <algorithm>
#include <iostream>
#include "../Modules/OSModule.hpp"
#include "../Modules/HostModule.hpp"
#include "../Modules/TimeModule.hpp"
#include "../Modules/RAMModule.hpp"
#include "../Modules/CPUModule.hpp"
#include "../Modules/BatteryModule.hpp"
#include <vector>
#include <string>
#include <map>
#include <functional>

namespace Krell {
    class Monitor;

    #define MODULE_LIST \
        MODULE(OSModule) \
        MODULE(HostModule) \
        MODULE(TimeModule) \
        MODULE(RAMModule) \
        MODULE(CPUModule) \
        MODULE(BatteryModule)

    class ModuleManager
    {
    public:
        enum class ModuleType {
            #define MODULE(name) name,
            MODULE_LIST
            #undef MODULE
        };

        ModuleManager();
        ~ModuleManager();
        void addModule(IModule *module);
        void removeModule(IModule *module);
        void updateModules();
        void printModules() const;
        const std::deque<IModule*>& getModules() const;
        void setMonitor(Monitor* monitor);
        Monitor* getMonitor() const;

        std::vector<std::string> listAvailableModules() const;
        void addModuleByIndex(size_t index);

        void moveModuleUp(void);
        void moveModuleDown(void);

    private:
        std::deque<IModule*> _modules;
        Monitor* _monitor = nullptr;
        std::vector<std::string> _availableModules;
        std::map<ModuleType, std::function<IModule*()>> _moduleFactory;
    };
}

#endif