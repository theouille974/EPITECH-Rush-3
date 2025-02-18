#ifndef OSMODULE_HPP
#define OSMODULE_HPP

#include "AModule.hpp"

namespace Krell {
    class OSModule : public AModule
    {
    public:
        OSModule();
        ~OSModule();

        void update() override;
    };
}

#endif