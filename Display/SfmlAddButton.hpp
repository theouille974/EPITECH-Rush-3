#ifndef SFMLADDBUTTON_H
#define SFMLADDBUTTON_H

#include <SFML/Graphics.hpp>
#include "../Core/ModuleManager.hpp"

namespace Krell {
    class AddModuleButton {
    public:
        AddModuleButton(ModuleManager& moduleManager, const sf::Font& font, const sf::Color& windowsColor, const sf::Color& textColor);
        void handleMouseClick(const sf::Vector2i& mousePos);
        void render(sf::RenderWindow& window);

    private:
        void displayAvailableModules(sf::RenderWindow& window);
        void handleAddModuleClick();
        void handleModuleSelection(const sf::Vector2i& mousePos);

        ModuleManager& _moduleManager;
        bool _showModuleList;
        sf::RectangleShape _button;
        sf::Text _buttonText;
        sf::Color _windows_color;
        sf::Color _text_color;
        std::vector<sf::Text> _moduleListTexts;
        std::vector<sf::RectangleShape> _moduleListRects;
    };
}

#endif