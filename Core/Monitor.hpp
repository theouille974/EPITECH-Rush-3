#ifndef MONITOR_H
#define MONITOR_H

#pragma once
#include "ModuleManager.hpp"
#include "../Display/IDisplay.hpp"
#include <memory>

namespace Krell {
    class Monitor
    {
    public:
        Monitor();
        ~Monitor();
        void run();
        void updateModules();
        void switchToSfml();
        void switchToNcurses();
        void endProgram();

    private:
        bool _useSfml = false;
        ModuleManager _moduleManager;
        std::unique_ptr<IDisplay> _display;
        bool _running = true;
    };
}

#endif