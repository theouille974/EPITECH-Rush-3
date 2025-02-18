#include "NcursesDisplay.hpp"
#include "../Core/Monitor.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Krell::NcursesDisplay::NcursesDisplay(ModuleManager& moduleManager)
    : _moduleManager(moduleManager), _height(40), _width(120), _posX(10), _posY(5), _keyPress("")
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    refresh();
}

Krell::NcursesDisplay::~NcursesDisplay()
{
    for (auto& win : _moduleWindows)
        delwin(win);
    endwin();
}

void Krell::NcursesDisplay::run(const std::deque<IModule*>& modules)
{
    char ch = 0;
    Monitor* monitor = dynamic_cast<Monitor*>(_moduleManager.getMonitor());
    while (ch != 'q') {
        monitor->updateModules();
        render(modules);

        timeout(200);
        ch = getch();

        if (ch == ' ') {
            monitor->switchToSfml();
            break;
        } else if (ch == 'A' || ch == 'a') {
            showAddModuleWindow();
        } else if (ch == 'D' || ch == 'd') {
            showDeleteModuleWindow();
        } else if (ch == 'U' || ch == 'u') {
            _moduleManager.moveModuleDown();
        } else if (ch == 'J' || ch == 'j') {
            _moduleManager.moveModuleUp();
        }
    }
    if (monitor) {
        monitor->endProgram();
    }
}

void Krell::NcursesDisplay::render(const std::deque<IModule*>& modules)
{
    start_color();
    use_default_colors();
    init_pair(1, COLOR_CYAN, -1);
    init_pair(2, COLOR_YELLOW, -1);

    _moduleWindows.clear();

    int startY = 3;

    for (const auto& module : modules) {
        if (!module) continue;

        std::string data = module->getData();
        std::vector<std::string> dataLines;
        size_t pos = 0;
        while ((pos = data.find(';')) != std::string::npos) {
            dataLines.push_back(data.substr(0, pos));
            data.erase(0, pos + 1);
        }
        dataLines.push_back(data);

        int requiredHeight = std::max(7, static_cast<int>(dataLines.size()) + 3);

        WINDOW* win = newwin(requiredHeight, _width, startY, 2);
        if (!win) {
            std::cerr << "Error: Module window creation failed!" << std::endl;
            continue;
        }

        _moduleWindows.push_back(win);
        startY += requiredHeight + 1;

        box(win, 0, 0);
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 1, "%-30s", module->getName().c_str());
        wattroff(win, COLOR_PAIR(1));

        int yOffset = 1;
        for (const auto& line : dataLines) {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, yOffset++, 1, "%-30s", line.c_str());
            wattroff(win, COLOR_PAIR(2));
        }

        wnoutrefresh(win);
    }

    doupdate();
}

void Krell::NcursesDisplay::showAddModuleWindow()
{
    std::vector<std::string> availableModules = _moduleManager.listAvailableModules();
    clear();
    refresh();
    WINDOW* addWin = newwin(LINES, COLS, 0, 0);
    box(addWin, 0, 0);
    mvwprintw(addWin, 1, 1, "ADD MODULE");
    for (size_t i = 0; i < availableModules.size(); ++i) {
        mvwprintw(addWin, 3 + i, 1, "%ld: %s", i, availableModules[i].c_str());
    }
    wrefresh(addWin);

    bool moduleSelected = false;
    while (!moduleSelected) {
        int ch = wgetch(addWin);
        if (ch >= '0' && ch <= '9') {
            size_t index = ch - '0';
            if (index < availableModules.size()) {
                _moduleManager.addModuleByIndex(index);
                moduleSelected = true;
            }
        }
    }

    delwin(addWin);
    clear();
    refresh();
}

void Krell::NcursesDisplay::showDeleteModuleWindow()
{
    const std::deque<IModule*>& modules = _moduleManager.getModules();
    clear();
    refresh();
    WINDOW* delWin = newwin(LINES, COLS, 0, 0);
    box(delWin, 0, 0);
    mvwprintw(delWin, 1, 1, "DELETE MODULE");
    for (size_t i = 0; i < modules.size(); ++i) {
        mvwprintw(delWin, 3 + i, 1, "%ld: %s", i, modules[i]->getName().c_str());
    }
    wrefresh(delWin);

    bool moduleSelected = false;
    std::string input;
    while (!moduleSelected) {
        int ch = wgetch(delWin);
        if (ch >= '0' && ch <= '9') {
            input += ch;
            mvwprintw(delWin, 2, 1, "Selected: %s", input.c_str());
            wrefresh(delWin);
        } else if (ch == '\n' && !input.empty()) {
            size_t index = std::stoi(input);
            if (index < modules.size()) {
                _moduleManager.removeModule(modules[index]);
                moduleSelected = true;
            }
        }
    }

    delwin(delWin);
    clear();
    refresh();
}