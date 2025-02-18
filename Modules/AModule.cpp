#include "AModule.hpp"

namespace Krell {
    AModule::AModule() {}

    AModule::~AModule() {}

    std::string AModule::getName() const {
        return _name;
    }

    std::string AModule::getData() const {
        return _data;
    }

    void AModule::renderSfml(sf::RenderWindow& /*window*/, const sf::Vector2f& /*position*/) const {
        // Default implementation does nothing
    }
}