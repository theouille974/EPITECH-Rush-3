#ifndef IMODULE_HPP
#define IMODULE_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace Krell {
    class IModule
    {
    public:
        virtual ~IModule() = default;
        virtual std::string getName() const = 0;
        virtual std::string getData() const = 0;
        virtual void update() = 0;
        virtual void renderSfml(sf::RenderWindow& window, const sf::Vector2f& position) const = 0;
    };
}

#endif