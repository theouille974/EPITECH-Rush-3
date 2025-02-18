#ifndef AMODULE_HPP
#define AMODULE_HPP

#include "IModule.hpp"

namespace Krell {
    class AModule : public IModule {
    public:
        AModule();
        virtual ~AModule();

        std::string getName() const override;
        std::string getData() const override;
        void renderSfml(sf::RenderWindow& window, const sf::Vector2f& position) const override;

    protected:
        std::string _name;
        std::string _data;
    };
}

#endif