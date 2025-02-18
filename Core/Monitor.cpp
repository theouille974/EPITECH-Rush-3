#include "Monitor.hpp"
#include "../Display/NcursesDisplay.hpp"
#include "../Display/SfmlDisplay.hpp"
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <thread>
#include <chrono>

namespace Krell {
    Monitor::Monitor()
    {
        _moduleManager.setMonitor(this);
    }

    Monitor::~Monitor()
    {
    }

    void Monitor::run()
    {
        _running = true;

        while (_running) {
            if (_useSfml) {
                _display = std::make_unique<SfmlDisplay>(_moduleManager);
            } else {
                _display = std::make_unique<NcursesDisplay>(_moduleManager);
            }

            _display->run(_moduleManager.getModules());
        }
    }

    void Monitor::updateModules()
    {
        _moduleManager.updateModules();
    }

    void Monitor::switchToSfml()
    {
        _useSfml = true;
        _running = false;
        _display.reset();
        run();
    }

    void Monitor::switchToNcurses()
    {
        _useSfml = false;
        _running = false;
        _display.reset();
        run();
    }

    void Monitor::endProgram()
    {
        _running = false;
    }
}