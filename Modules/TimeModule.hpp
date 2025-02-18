#ifndef TIMEMODULE_HPP
#define TIMEMODULE_HPP

#include "AModule.hpp"
#include <ctime>

namespace Krell {
    class TimeModule : public AModule
    {
    public:
        TimeModule();
        ~TimeModule();

        void update() override;
        void renderSfml(sf::RenderWindow& window, const sf::Vector2f& position) const override;
    };
}

#endif