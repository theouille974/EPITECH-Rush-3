#ifndef NCURSESDISPLAY_H
#define NCURSESDISPLAY_H

#include "IDisplay.hpp"
#include "../Core/ModuleManager.hpp"
#include <ncurses.h>
#include <deque>
#include <vector>

namespace Krell {
    class NcursesDisplay : public IDisplay {
    public:
        NcursesDisplay(ModuleManager& moduleManager);
        ~NcursesDisplay();
        void run(const std::deque<IModule*>& modules) override;

    private:
        void render(const std::deque<IModule*>& modules);
        void showAddModuleWindow();
        void showDeleteModuleWindow();
        ModuleManager& _moduleManager;
        int _height, _width, _posX, _posY;
        std::string _keyPress;
        WINDOW* _win;
        std::vector<WINDOW*> _moduleWindows;
    };
}

#endif