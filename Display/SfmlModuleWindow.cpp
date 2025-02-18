#include "SfmlModuleWindow.hpp"
#include <sstream>

namespace Krell {
    SfmlModuleWindow::SfmlModuleWindow(IModule* module, const sf::Font& font, const sf::Vector2f& position, float windowWidth)
        : _module(module), _isClosed(false)
    {
        _background.setSize(sf::Vector2f(windowWidth - 20, 150));
        _background.setPosition(position);
        _background.setFillColor(sf::Color(108, 108, 108));

        _title.setFont(font);
        _title.setString(module->getName());
        _title.setCharacterSize(24);
        _title.setFillColor(sf::Color::White);
        _title.setPosition(position.x + 10, position.y + 10);

        _data.setFont(font);
        _data.setString(module->getData());
        _data.setCharacterSize(18);
        _data.setFillColor(sf::Color::White);
        _data.setPosition(position.x + 10, position.y + 50);

        _closeButton.setSize(sf::Vector2f(20, 20));
        _closeButton.setFillColor(sf::Color::Red);
        _closeButton.setPosition(position.x + windowWidth - 40, position.y + 10);
    }

    void SfmlModuleWindow::render(sf::RenderWindow& window)
    {
        window.draw(_background);
        window.draw(_title);
        window.draw(_data);
        window.draw(_closeButton);

        // Call the module's special rendering function
        sf::Vector2f position = _background.getPosition();
        position.x += 300;
        _module->renderSfml(window, position);
    }

    bool SfmlModuleWindow::handleEvent(const sf::Event& event, const sf::Vector2i& mousePos)
    {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (_closeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                _isClosed = true;
                return true;
            }
        }
        return false;
    }

    bool SfmlModuleWindow::isClosed() const
    {
        return _isClosed;
    }

    IModule* SfmlModuleWindow::getModule() const
    {
        return _module;
    }
}