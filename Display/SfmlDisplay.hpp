/*
** EPITECH PROJECT, 2025
** SFMLDisplay
** File description:
** SFMLDisplay
*/

#ifndef SFMLDISPLAY_H
#define SFMLDISPLAY_H

#include "IDisplay.hpp"
#include "SfmlModuleWindow.hpp"
#include "SfmlAddButton.hpp"
#include "../Core/ModuleManager.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#pragma once

#include <SFML/System/Clock.hpp> 

namespace Krell {
    class SfmlDisplay : public IDisplay
    {
    public:
        SfmlDisplay(ModuleManager& moduleManager);
        ~SfmlDisplay();

        void run(const std::deque<IModule*>& modules) override;
        void render(const std::deque<IModule*>& modules) override;

    private:
        void handleResize(unsigned int width, unsigned int height);

    protected:
        sf::RenderWindow _window;
        sf::Color _background_color;
        sf::Color _windows_color;
        sf::Color _text_color;
        sf::Font _font;
        std::vector<SfmlModuleWindow> _moduleWindows;
        ModuleManager& _moduleManager;
        AddModuleButton _addModuleButton;
        sf::Clock _clock;
        float _scrollOffset = 0;
    };
}

#endif