#include "SfmlDisplay.hpp"
#include "../Core/Monitor.hpp"
#include <iostream>

namespace Krell {
    SfmlDisplay::SfmlDisplay(ModuleManager& moduleManager) 
        : _window(sf::VideoMode(800, 600), "SFML Window"),
          _moduleManager(moduleManager),
          _addModuleButton(moduleManager, _font, sf::Color(108, 108, 108), sf::Color(255, 255, 255))
    {
        _background_color = sf::Color(57, 77, 205);
        _windows_color  = sf::Color(108, 108, 108);
        _text_color = sf::Color(255, 255, 255);
        if (!_font.loadFromFile("Display/assets/W95FA.otf")) {
            std::cerr << "Error loading font" << std::endl;
        }
    }

    SfmlDisplay::~SfmlDisplay() 
    {
        if (_window.isOpen()) {
            _window.close();
        }
    }

    void SfmlDisplay::run(const std::deque<IModule*>& modules)
    {
        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    dynamic_cast<Monitor*>(_moduleManager.getMonitor())->endProgram();
                    _window.close();
                    return;
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Space) {
                        _window.close();
                        dynamic_cast<Monitor*>(_moduleManager.getMonitor())->switchToNcurses();
                        return;
                    } else if (event.key.code == sf::Keyboard::U) {
                        _moduleManager.moveModuleUp();
                    } else if (event.key.code == sf::Keyboard::J) {
                        _moduleManager.moveModuleDown();
                    }
                }
                if (event.type == sf::Event::Resized) {
                    handleResize(event.size.width, event.size.height);
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                    _addModuleButton.handleMouseClick(mousePos);
                    for (auto& moduleWindow : _moduleWindows) {
                        if (moduleWindow.handleEvent(event, mousePos)) {
                            _moduleManager.removeModule(moduleWindow.getModule());
                        }
                    }
                }
                if (event.type == sf::Event::MouseWheelScrolled) {
                    if (event.mouseWheelScroll.delta > 0) {
                        _scrollOffset -= 20;
                    } else {
                        _scrollOffset += 20;
                    }
                    _scrollOffset = std::max(_scrollOffset, 0.0f);
                    _scrollOffset = std::min(_scrollOffset, std::max(0.0f, static_cast<float>(_moduleWindows.size() * 160 - _window.getSize().y + 60)));
                }
            }

            dynamic_cast<Monitor*>(_moduleManager.getMonitor())->updateModules();

            _window.clear(_background_color);

            render(modules);

            _addModuleButton.render(_window);

            _window.display();
        }
    }

    void SfmlDisplay::render(const std::deque<IModule*>& modules)
    {
        _moduleWindows.clear();
        sf::Vector2f position(10, 60 - _scrollOffset);
        float windowWidth = _window.getSize().x;
        for (const auto& module : modules) {
            _moduleWindows.emplace_back(module, _font, position, windowWidth);
            position.y += 160;
        }

        for (auto& moduleWindow : _moduleWindows) {
            if (!moduleWindow.isClosed()) {
                moduleWindow.render(_window);
            }
        }
    }

    void SfmlDisplay::handleResize(unsigned int width, unsigned int height)
    {
        sf::FloatRect visibleArea(0, 0, width, height);
        _window.setView(sf::View(visibleArea));
    }
}