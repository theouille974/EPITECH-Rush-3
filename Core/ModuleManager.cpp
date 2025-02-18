#include "ModuleManager.hpp"
#include "Monitor.hpp"
#include <iostream>
#include <algorithm>
#include "../Modules/OSModule.hpp"
#include "../Modules/HostModule.hpp"
#include "../Modules/TimeModule.hpp"
#include "../Modules/RAMModule.hpp"
#include "../Modules/CPUModule.hpp"
#include "../Modules/BatteryModule.hpp"

namespace Krell {
    ModuleManager::ModuleManager() {
        _modules.push_back(new OSModule());
        _modules.push_back(new HostModule());
        _modules.push_back(new TimeModule());

        #define MODULE(name) _availableModules.push_back(#name);
        MODULE_LIST
        #undef MODULE

        _moduleFactory = {
            #define MODULE(name) {ModuleType::name, []() { return new name(); }},
            MODULE_LIST
            #undef MODULE
        };
    }

    ModuleManager::~ModuleManager() {
        for (auto module : _modules) {
            delete module;
        }
    }

    void ModuleManager::addModule(IModule *module) {
        _modules.push_back(module);
    }

    void ModuleManager::removeModule(IModule *module) {
        auto it = std::find(_modules.begin(), _modules.end(), module);
        if (it != _modules.end()) {
            delete *it;
            _modules.erase(it);
        }
    }

    void ModuleManager::updateModules() {
        for (auto module : _modules) {
            module->update();
        }
    }

    void ModuleManager::printModules() const {
        for (const auto& module : _modules) {
            std::cout << module->getName() << ": " << module->getData() << std::endl;
        }
    }

    const std::deque<IModule*>& ModuleManager::getModules() const {
        return _modules;
    }

    void ModuleManager::setMonitor(Monitor* monitor) {
        _monitor = monitor;
    }

    Monitor* ModuleManager::getMonitor() const {
        return _monitor;
    }

    std::vector<std::string> ModuleManager::listAvailableModules() const {
        return _availableModules;
    }

    void ModuleManager::addModuleByIndex(size_t index) {
        if (index >= _availableModules.size()) {
            return;
        }

        ModuleType moduleType = static_cast<ModuleType>(index);
        auto it = _moduleFactory.find(moduleType);
        if (it != _moduleFactory.end()) {
            IModule* module = it->second();
            if (module) {
                addModule(module);
            }
        }
    }

    void ModuleManager::moveModuleUp() {
        if (!_modules.empty()) {
            std::rotate(_modules.rbegin(), _modules.rbegin() + 1, _modules.rend());
        }
    }

    void ModuleManager::moveModuleDown() {
        if (!_modules.empty()) {
            std::rotate(_modules.begin(), _modules.begin() + 1, _modules.end());
        }
    }
}