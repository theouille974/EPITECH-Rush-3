#include "BatteryModule.hpp"

Krell::BatteryModule::BatteryModule()
{
    _name = "Battery Module";
    update();
}

Krell::BatteryModule::~BatteryModule()
{

}

void Krell::BatteryModule::update()
{
    std::ifstream file("/sys/class/power_supply/BAT0/capacity");
    if (file.is_open()) {
        file >> _data;
        _data += "%";
        file.close();
    } else {
        std::cerr << "Failed to read battery status." << std::endl;
    }
}

void Krell::BatteryModule::renderSfml(sf::RenderWindow& window, const sf::Vector2f& position) const
{
    sf::Texture texture;
    if (!texture.loadFromFile("Display/assets/02_-_Single_Energizer_Battery.jpg")) {
        std::cerr << "Error loading image" << std::endl;
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(position);

    sprite.setScale(0.1f, 0.1f);

    window.draw(sprite);
}