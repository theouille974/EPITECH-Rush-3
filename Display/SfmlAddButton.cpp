#include "SfmlAddButton.hpp"
#include <iostream>

namespace Krell {
    AddModuleButton::AddModuleButton(ModuleManager& moduleManager, const sf::Font& font, const sf::Color& windowsColor, const sf::Color& textColor)
        : _moduleManager(moduleManager), _showModuleList(false), _windows_color(windowsColor), _text_color(textColor)
    {
        _button.setSize(sf::Vector2f(100, 40));
        _button.setFillColor(_windows_color);
        _button.setOutlineThickness(5);

        sf::Color outlineColor = _windows_color;
        outlineColor.r = std::max(0, outlineColor.r - 20);
        outlineColor.g = std::max(0, outlineColor.g - 20);
        outlineColor.b = std::max(0, outlineColor.b - 20);
        _button.setOutlineColor(outlineColor);

        _button.setPosition(0, 0);
        _buttonText.setFont(font);
        _buttonText.setString("Add Module");
        _buttonText.setCharacterSize(15);
        _buttonText.setFillColor(_text_color);
        _buttonText.setPosition(10, 10);

        std::vector<std::string> moduleNames = _moduleManager.listAvailableModules();
        for (size_t i = 0; i < moduleNames.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(moduleNames[i]);
            text.setCharacterSize(15);
            text.setFillColor(_text_color);
            text.setPosition(10, 60 + i * 50);
            _moduleListTexts.push_back(text);

            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(100, 40));
            rect.setFillColor(_windows_color);
            rect.setOutlineThickness(5);
            rect.setOutlineColor(outlineColor);
            rect.setPosition(0, 60 + i * 50);
            _moduleListRects.push_back(rect);
        }
    }

    void AddModuleButton::handleMouseClick(const sf::Vector2i& mousePos)
    {
        if (_button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            handleAddModuleClick();
        } else if (_showModuleList) {
            handleModuleSelection(mousePos);
        }
    }

    void AddModuleButton::render(sf::RenderWindow& window)
    {
        window.draw(_button);
        window.draw(_buttonText);
        if (_showModuleList) {
            displayAvailableModules(window);
        }
    }

    void AddModuleButton::displayAvailableModules(sf::RenderWindow& window)
    {
        for (const auto& rect : _moduleListRects) {
            window.draw(rect);
        }
        for (const auto& text : _moduleListTexts) {
            window.draw(text);
        }
    }

    void AddModuleButton::handleAddModuleClick()
    {
        _showModuleList = !_showModuleList;
    }

    void AddModuleButton::handleModuleSelection(const sf::Vector2i& mousePos)
    {
        for (size_t i = 0; i < _moduleListRects.size(); ++i) {
            if (_moduleListRects[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                _moduleManager.addModuleByIndex(i);
                _showModuleList = false;
                break;
            }
        }
    }
}