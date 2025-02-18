#ifndef BATTERYMODULE_H
#define BATTERYMODULE_H

#pragma once
#include "AModule.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

namespace Krell {
    class BatteryModule: public AModule {
    public:
        BatteryModule();
        ~BatteryModule();
        void update() override;
        void renderSfml(sf::RenderWindow& window, const sf::Vector2f& position) const override;
    };
}

#endif