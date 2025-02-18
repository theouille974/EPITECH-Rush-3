/*
** EPITECH PROJECT, 2025
** RAMModule
** File description:
** RAMModule
*/

#ifndef RAMMODULE_H
#define RAMMODULE_H

#pragma once
#include "AModule.hpp"
#include <iostream>
#include <fstream>

namespace Krell {
    class RAMModule : public AModule {
    public:
        RAMModule();
        ~RAMModule();

        void update() override;
        void displayMemoryInfo();
        void renderSfml(sf::RenderWindow& window, const sf::Vector2f& position) const override;

    private:
        long _totalRAM;
        long _freeRAM;
    };
}

#endif