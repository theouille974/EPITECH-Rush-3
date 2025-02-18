#ifndef SFMLMODULEWINDOW_HPP
#define SFMLMODULEWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "../Modules/IModule.hpp"

namespace Krell {
    class SfmlModuleWindow
    {
    public:
        SfmlModuleWindow(IModule* module, const sf::Font& font, const sf::Vector2f& position, float windowWidth);
        void render(sf::RenderWindow& window);
        bool handleEvent(const sf::Event& event, const sf::Vector2i& mousePos);
        bool isClosed() const;
        IModule* getModule() const;

    private:
        IModule* _module;
        sf::RectangleShape _background;
        sf::Text _title;
        sf::Text _data;
        sf::RectangleShape _closeButton;
        bool _isClosed;
    };
}

#endif