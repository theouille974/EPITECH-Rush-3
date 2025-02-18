#include "RAMModule.hpp"
#include <sstream>

Krell::RAMModule::RAMModule()
{
    _name = "RAM Module";
    update();
}

Krell::RAMModule::~RAMModule()
{
}

void Krell::RAMModule::update()
{
    std::ifstream file("/proc/meminfo");
    std::string label;
    long value;
    std::string unit;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open /proc/meminfo" << std::endl;
        return;
    }

    while (file >> label >> value >> unit) {
        if (label == "MemTotal:") {
            _totalRAM = value;
        }
        else if (label == "MemAvailable:") {
            _freeRAM = value;
            break;
        }
    }
    file.close();

    displayMemoryInfo();
}

void Krell::RAMModule::displayMemoryInfo()
{
    long usedRAM = _totalRAM - _freeRAM;
    double ramUsagePercent = (static_cast<double>(usedRAM) / _totalRAM) * 100.0;

    this->_data = "Total RAM: " + std::to_string(_totalRAM / 1024) + " MB;";
    this->_data += "Free RAM: " + std::to_string(_freeRAM / 1024) + " MB;";
    this->_data += "Used RAM: " + std::to_string(usedRAM / 1024) + " MB;";
    this->_data += "RAM Usage: " + std::to_string(ramUsagePercent) + " %";
}

void Krell::RAMModule::renderSfml(sf::RenderWindow& window, const sf::Vector2f& position) const
{
    long usedRAM = _totalRAM - _freeRAM;
    double ramUsagePercent = (static_cast<double>(usedRAM) / _totalRAM) * 100.0;

    sf::Vector2f newPosition = position;
    newPosition.x += 400;

    sf::RectangleShape square(sf::Vector2f(100, 100));
    square.setFillColor(sf::Color::Green);
    square.setPosition(newPosition);

    sf::RectangleShape usage(sf::Vector2f(100, 100 * (ramUsagePercent / 100.0)));
    usage.setFillColor(sf::Color::Red);
    usage.setPosition(newPosition.x, newPosition.y + 100 - usage.getSize().y);

    window.draw(square);
    window.draw(usage);
}