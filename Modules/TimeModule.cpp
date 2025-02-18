#include "TimeModule.hpp"
#include <iostream>

Krell::TimeModule::TimeModule() : AModule()
{
    _name = "Time Module";
    update();
}

Krell::TimeModule::~TimeModule()
{

}

void Krell::TimeModule::update()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    this->_data = "Time: " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + '\n';
    this->_data += "Date: " + std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(ltm->tm_mday) + "/" + std::to_string(1900 + ltm->tm_year);
}

void Krell::TimeModule::renderSfml(sf::RenderWindow& window, const sf::Vector2f& position) const
{
    sf::Font font;
    if (!font.loadFromFile("Display/assets/W95FA.otf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    sf::Text timeText;
    timeText.setFont(font);
    timeText.setString(_data);
    timeText.setCharacterSize(48); // Big text
    timeText.setFillColor(sf::Color::Red); // Red color
    timeText.setPosition(position);

    window.draw(timeText);
}